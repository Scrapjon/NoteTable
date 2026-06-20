// Copyright Oliver Moloney


#include "UI/NWindowWidget.h"

#include "SlateOptMacros.h"
#include "Components/RichTextBlock.h"
#include "UI/NWindowDetails.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SNWindowWidget::Construct(const FArguments& InArgs) {
	// Constants
	
	constexpr float TextBoxWidth = 0.4f;
	
	constexpr float RichTextBoxWidth = 0.4f;
	
	constexpr float DetailsBoxWidth = 1.f - TextBoxWidth - RichTextBoxWidth;
	
	TObjectPtr<UNWindowDetails> WindowDetails = NewObject<UNWindowDetails>();
	
	// Rich Text Block for text preview
	URichTextBlock* RichTextBlock = NewObject<URichTextBlock>(GEditor->GetEditorWorldContext().World()); // TODO: maybe come up with a better name for this...
	TSharedRef<SBox> RichTextBox = SNew(SBox);
	RichTextBox->SetContent(RichTextBlock->TakeWidget());
	
	// Property Details Panel
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	
	
	
	TSharedRef<IDetailsView> DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	
	DetailsView->SetObject(WindowDetails);
	
	
	// Bindings
	
	TextChangedSignature.BindLambda([RichTextBlock](const FText& Text) {
		RichTextBlock->SetText(Text);
	});
	
	auto OnFinishChangingProperties = [RichTextBlock, WindowDetails, RichTextBox](const FPropertyChangedEvent& PropertyChangedEvent) {
		if (!WindowDetails) return;
		FText CurrentText = RichTextBlock->GetText();
		RichTextBlock->SetTextStyleSet(WindowDetails->TextStyleSet);
		RichTextBox->SetContent(RichTextBlock->TakeWidget());
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
