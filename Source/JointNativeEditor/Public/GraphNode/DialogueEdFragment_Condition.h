//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Condition.generated.h"

class UVoltAnimationManager;
class SScrollBox;
class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Condition : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Condition();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;

public:
	
	virtual void ModifyGraphNodeSlate() override;

	
public:

	TSharedPtr<SVerticalBox> ConditionInstanceBox;
	
};
