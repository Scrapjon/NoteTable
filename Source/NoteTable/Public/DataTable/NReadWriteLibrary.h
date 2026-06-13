// Copyright Oliver Moloney

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NReadWriteLibrary.generated.h"

class FJsonObject;

USTRUCT(BlueprintType)
struct FNoteTableTextData {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString EntryName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TextContent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRichTextStyleRow StyleRow; 
	
};


/**
 * 
 */
UCLASS()
class NOTETABLE_API UNReadWriteLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
public:
	// File reading and writing code adapted from Alex Quevillon
	
	UFUNCTION(BlueprintCallable, Category="Data|Text|Read")
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
	UFUNCTION(BlueprintCallable, Category="Data|Text|Write")
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);
	
	
	static TSharedPtr<FJsonObject> ReadJson(const FString& JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
	static void WriteJson(const FString& JsonFilePath, const TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess, FString& OutInfoMessage);
	
	UFUNCTION(BlueprintCallable, Category="Data|Json|Read")
	static FNoteTableTextData ReadTextDataFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
	UFUNCTION(BlueprintCallable, Category="Data|Json|Write")
	static void WriteTextDataToJsonFile(FString JsonFilePath, FNoteTableTextData TextData, bool& bOutSuccess, FString& OutInfoMessage);
};
