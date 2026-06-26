// Copyright Oliver Moloney

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SRichTextBlock;
class UNWindowDetails;

struct FRichTextStyleData {
	
	TSharedPtr<FSlateStyleSet> StyleInstance;
	TSharedPtr<SBox> PreviewContainer;
	TSharedPtr<SRichTextBlock> PreviewBlock;
	
};

/**
 * 
 */
class NOTETABLE_API SNWindowWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SNWindowWidget) {
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual ~SNWindowWidget() override;
private:
	
	void RebuildPreview();
	FText CurrentText;
	
	FOnTextChanged TextChangedSignature;
	FOnFinishedChangingProperties FinishedChangingPropertiesSignature;
	
	TObjectPtr<UNWindowDetails> WindowDetails;
	FRichTextStyleData RichTextStyleData;
};
