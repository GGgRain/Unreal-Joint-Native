//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Sequence.generated.h"

/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Sequence : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Sequence();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;

	virtual void ModifyGraphNodeSlate() override;
	
};
