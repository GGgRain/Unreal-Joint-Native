//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/JointEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Participant.generated.h"

class SVerticalBox;
class UVoltAnimationManager;
class SScrollBox;
class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Participant : public UJointEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Participant();

public:

	virtual TSubclassOf<UJointNodeBase> SupportedNodeClass() override;

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
