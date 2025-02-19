//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/JointEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Select.generated.h"

class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Select : public UJointEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Select();

public:
	
	virtual TSubclassOf<UJointNodeBase> SupportedNodeClass() override;
	
	FPinConnectionResponse CanAttachSubNodeOnThis(const UJointEdGraphNode* InSubNode) const override;
	
public:
	
	virtual void AllocateDefaultPins() override;

	virtual void ReallocatePins() override;

	virtual void NodeConnectionListChanged() override;

public:

	UPROPERTY(Transient)
	bool bHasTransaction = false;
	
};
