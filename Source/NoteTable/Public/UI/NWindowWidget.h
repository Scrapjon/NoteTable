// Copyright Oliver Moloney

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

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
	
	FOnTextChanged TextChangedSignature;
};
