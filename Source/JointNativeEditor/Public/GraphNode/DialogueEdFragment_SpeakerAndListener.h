//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_SpeakerAndListener.generated.h"

class SScrollBox;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_SpeakerAndListener : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;

	virtual void ModifyGraphNodeSlate() override;

	virtual void OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName) override;

	void UpdateSlate();

public:

	TSharedPtr<SScrollBox> SpeakersBox;
	
	TSharedPtr<SScrollBox> ListenersBox;
	
};
