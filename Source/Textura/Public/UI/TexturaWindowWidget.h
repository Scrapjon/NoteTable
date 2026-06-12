// Copyright Oliver Moloney

#pragma once

#include "CoreMinimal.h"
#include "Textura.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */


class TEXTURA_API STexturaWindowWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(STexturaWindowWidget) {
		}
		
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	
	FOnTextChanged TextChangedSignature;
};
