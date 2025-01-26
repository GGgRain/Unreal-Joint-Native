//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Select.generated.h"

class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Select : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Select();

public:
	
	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;
	
	FPinConnectionResponse CanAttachSubNodeOnThis(const UDialogueEdGraphNode* InSubNode) const override;
	
public:
	
	virtual void AllocateDefaultPins() override;

	virtual void NodeConnectionListChanged() override;

public:

	UPROPERTY(Transient)
	bool bHasTransaction = false;
	
};
