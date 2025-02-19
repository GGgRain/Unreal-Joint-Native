//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/JointEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Sequence.generated.h"

/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Sequence : public UJointEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Sequence();

public:

	virtual TSubclassOf<UJointNodeBase> SupportedNodeClass() override;

	virtual void ModifyGraphNodeSlate() override;
	
};
