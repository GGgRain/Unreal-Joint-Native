//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"

#include "DF_Text.generated.h"

/**
 * A fragment that contains a text.
 * Can be used in multiple occasion.
 */
UCLASS(Category = "Joint|Native|Core|Text")
class JOINTNATIVE_API UDF_Text: public UDialogueFragment
{
	GENERATED_BODY()

public:
	
	UDF_Text();

public:
	
	/**
	 * A text this text fragment contains.
	 * Can be used in various occasions where you need a text on the system, such as the dialogue widget text or select node.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Text;

public:

	/**
	 * A text style fragment the text can use.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FDialogueNodePointer TextStyleInstance;

	/**
	 * Get the text style table if it has any for the stylization. This is optional.
	 * @return The text style table for the text.
	 */
	UDataTable* GetTextStyleTableIfPresent() const;
	
};
