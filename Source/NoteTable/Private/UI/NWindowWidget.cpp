// Copyright Oliver Moloney


#include "UI/NWindowWidget.h"

#include "SlateOptMacros.h"
#include "Components/RichTextBlock.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "UI/NWindowDetails.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Text/SRichTextBlock.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SNWindowWidget::Construct(const FArguments& InArgs) {
	// Constants
	
	constexpr float TextBoxWidth = 0.4f;
	
	constexpr float RichTextBoxWidth = 0.4f;
	
	constexpr float DetailsBoxWidth = 1.f - TextBoxWidth - RichTextBoxWidth;
	
	WindowDetails = NewObject<UNWindowDetails>();
	WindowDetails->AddToRoot();
	
	// Rich Text Block for text preview
	
	// TODO: maybe come up with a better name for this...
	URichTextBlock* RichTextBlockObj = NewObject<URichTextBlock>(GEditor->GetEditorWorldContext().World());
	
	TSharedRef<SBox> RichTextBox = SNew(SBox);
	
	RichTextBox->SetContent(RichTextBlockObj->TakeWidget());
	
	// Property Details Panel
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	
	
	
	TSharedRef<IDetailsView> DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	
	DetailsView->SetObject(WindowDetails);
	
	
	// Bindings
	
	TextChangedSignature.BindLambda([RichTextBlockObj](const FText& Text) {
		RichTextBlockObj->SetText(Text);
	});
	
	auto OnFinishChangingProperties = [this, RichTextBlockObj, RichTextBox](const FPropertyChangedEvent& PropertyChangedEvent) {
		if (!WindowDetails) return;
		FText CurrentText = RichTextBlockObj->GetText();
		RichTextBlockObj->SetTextStyleSet(WindowDetails->TextStyleSet);
		RichTextBox->SetContent(RichTextBlockObj->TakeWidget());
	};
	
	DetailsView->OnFinishedChangingProperties().AddLambda(
		OnFinishChangingProperties);
	
	// Input Text Box
	const TSharedRef<SMultiLineEditableTextBox> InputTextBox = SNew(SMultiLineEditableTextBox) // TODO: maybe come up with a better name for this...
		.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
		.OnTextChanged(TextChangedSignature);
	
	ChildSlot [
		SNew(SVerticalBox) + SVerticalBox::Slot()
		.FillHeight(1.f)
			[
				SNew(SHorizontalBox) + SHorizontalBox::Slot().FillWidth(TextBoxWidth)
				[
					InputTextBox
				]
				+ SHorizontalBox::Slot().FillWidth(RichTextBoxWidth)
				[
					RichTextBox
				]
				+ SHorizontalBox::Slot().FillWidth(DetailsBoxWidth)
				[
					DetailsView
				]
			]
	];
}

SNWindowWidget::~SNWindowWidget() {
	WindowDetails->RemoveFromRoot();
}

void SNWindowWidget::RebuildPreview() {
	TObjectPtr<UDataTable> StyleTable = WindowDetails->TextStyleSet;
	
	RichTextStyleData.StyleInstance = MakeShareable(new FSlateStyleSet("NoteTableRichText"));
	
	FTextBlockStyle DefaultStyle = FTextBlockStyle()
	.SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12))
	.SetColorAndOpacity(FLinearColor::White);
	
	if (StyleTable) {
		for (const TPair<FName, uint8*>& Row : StyleTable->GetRowMap()) {
			const FRichTextStyleRow* StyleRow = reinterpret_cast<FRichTextStyleRow*>(Row.Value);
			RichTextStyleData.StyleInstance->Set(Row.Key, StyleRow->TextStyle);
			if (Row.Key == FName("Default")) {
				DefaultStyle = StyleRow->TextStyle;
			}
		}
	}
	
	TArray<TSharedRef<ITextDecorator>> Decorators;
	
	TSharedRef<FRichTextLayoutMarshaller> Marshaller = 
		FRichTextLayoutMarshaller::Create(nullptr, nullptr, Decorators, RichTextStyleData.StyleInstance.Get());
	
	RichTextStyleData.PreviewBlock = SNew(SRichTextBlock)
		.Text(CurrentText)
		.TextStyle(&DefaultStyle)
		.Marshaller(Marshaller)
		.AutoWrapText(true);
	RichTextStyleData.PreviewContainer->SetContent(RichTextStyleData.PreviewBlock.ToSharedRef());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
