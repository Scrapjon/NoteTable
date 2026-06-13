// Copyright Oliver Moloney


#include "UI/NWindowWidget.h"

#include "SlateOptMacros.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Text/SRichTextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SNWindowWidget::Construct(const FArguments& InArgs) {
	// Constants
	
	constexpr float TextBoxWidth = 1000.f;
	constexpr float TextBoxHeight = 480.f;
	constexpr float TextBoxPadding = 10.f;
	
	constexpr float RichTextBoxWidth = TextBoxWidth;
	constexpr float RichTextBoxHeight = TextBoxHeight;
	constexpr float RichTextBoxPadding = TextBoxPadding;
	
	// Rich Text Block for text preview
	const TSharedRef<SRichTextBlock> RichTextBlock = SNew(SRichTextBlock); // TODO: maybe come up with a better name for this...
	
	// Bindings
	
	TextChangedSignature.BindLambda([RichTextBlock](const FText& Text) {
		RichTextBlock->SetText(Text);
	});
	
	// Input Text Box
	const TSharedRef<SMultiLineEditableTextBox> InputTextBox = SNew(SMultiLineEditableTextBox) // TODO: maybe come up with a better name for this...
		.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
		.OnTextChanged(TextChangedSignature);
	
	ChildSlot [
		SNew(SVerticalBox) + SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox) + SHorizontalBox::Slot()
				[
					SNew(SBox).MinDesiredWidth(TextBoxWidth).MinDesiredHeight(TextBoxHeight).Padding(TextBoxPadding)
					[
						InputTextBox
					]    
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox).MinDesiredWidth(RichTextBoxWidth).MinDesiredHeight(RichTextBoxHeight).Padding(RichTextBoxPadding)
					[
						RichTextBlock
					]
				]
			]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
