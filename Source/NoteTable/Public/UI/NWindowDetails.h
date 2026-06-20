// Copyright Oliver Moloney

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NWindowDetails.generated.h"

/**
 * 
 */
UCLASS()
class NOTETABLE_API UNWindowDetails : public UObject {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (RequiredAssetDataTags = "RowStructure=/Script/UMG.RichTextStyleRow"))
	TObjectPtr<UDataTable> TextStyleSet;
	
	
};
