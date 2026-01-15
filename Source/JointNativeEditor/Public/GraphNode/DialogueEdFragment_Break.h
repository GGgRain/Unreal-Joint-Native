//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/JointEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Break.generated.h"

class UVoltAnimationManager;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Break : public UJointEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Break();

public:

	virtual TSubclassOf<UJointNodeBase> SupportedNodeClass() override;
	
public:

	virtual void AllocateDefaultPins() override;
	
	virtual void ReallocatePins() override;
	
	virtual void NodeConnectionListChanged() override;

};
