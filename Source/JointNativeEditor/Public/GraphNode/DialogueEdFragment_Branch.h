//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Branch.generated.h"

class UVoltAnimationManager;
class SScrollBox;
class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Branch : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Branch();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;
	
	virtual void OnCompileNode() override;

public:

	virtual void AllocateDefaultPins() override;

	virtual void ReallocatePins() override;

	virtual void NodeConnectionListChanged() override;

public:

	virtual FPinConnectionResponse CanAttachSubNodeOnThis(const UDialogueEdGraphNode* InSubNode) const override;

public:

	TSharedPtr<SScrollBox> ConditionList;

};
