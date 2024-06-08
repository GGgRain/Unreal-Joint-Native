//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"

#include "DF_TextStyle.generated.h"

/**
 * 
 */
UCLASS(Category = "Joint|Native|Core|Text")
class JOINTNATIVE_API UDF_TextStyle: public UDialogueFragment
{
	GENERATED_BODY()

public:
	
	UDF_TextStyle();

public:
	
	
	/**
	 * A text style table for the text styling.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	UDataTable* TextStyleTable;
	
};
