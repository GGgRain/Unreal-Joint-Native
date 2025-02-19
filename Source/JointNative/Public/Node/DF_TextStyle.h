//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_TextStyle.generated.h"

/**
 * A fragment that contains text style table (Rich Text) for the graph.
 * Use this fragment to feed text styles on the text fragments on your graph.
 */
UCLASS(Category = "Joint Native|C++|Text", DisplayName="Text Style")
class JOINTNATIVE_API UDF_TextStyle: public UJointFragment
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
