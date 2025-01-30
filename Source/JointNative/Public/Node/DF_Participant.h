//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"
#include "DF_Participant.generated.h"

class UDialogueParticipantComponent;

/**
 * A fragment that represent specific participant component on the graph.
 * You can access the participant with this node.
 * This node can be used in various situation when you need to get the reference of the participant in the graph.
 */
UCLASS(Category = "Joint|Native|Core|Participant")
class JOINTNATIVE_API UDF_Participant: public UDialogueFragment
{
	GENERATED_BODY()

public:

	UDF_Participant();
	
	/**
	 * The identification tag for the components that participant the conversation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Participant Data")
	FGameplayTag ParticipantTag;

public:

	/**
	 * The pointer to the participant component instance this node represent.
	 * You can set this value to specify the component.
	 * If this value was nullptr, then it will try to search it on the world at runtime.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Participant Reference")
	UDialogueParticipantComponent* ParticipantComponentInstance = nullptr;

	
	/**
	 * Whether to allow collecting the participant the ParticipantTag refers to.
	 * If true, it will try to get the component reference in the world when OnNodeBeginPlay() has been triggered and fill the ParticipantComponentInstance with the found reference.
	 * If the ParticipantComponentInstance's value was specified before the execution, the node will ignore this value and will not perform the auto collecting.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Participant Reference")
	bool bAllowCollectingParticipantComponentOnWorldAutomatically = true;

public:

	/**
	 * Get the participant component this node represent.
	 * @return The participant component this node represent.
	 */
	UFUNCTION(BlueprintPure, Category="Participant")
	UDialogueParticipantComponent* GetParticipantComponent();


public:

	virtual void PostNodeBeginPlay_Implementation() override;
};
