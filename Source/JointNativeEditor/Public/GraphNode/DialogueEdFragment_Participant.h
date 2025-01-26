//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Participant.generated.h"

class UVoltAnimationManager;
class SScrollBox;
class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Participant : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Participant();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;

public:

	virtual void ModifyGraphNodeSlate() override;

	virtual void OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName) override;
	
	void UpdateSlate();

public:
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

public:

	/**
	 * A box that holds the condition representing slate.
	 */
	TSharedPtr<SVerticalBox> ParticipantBox;
	
};
