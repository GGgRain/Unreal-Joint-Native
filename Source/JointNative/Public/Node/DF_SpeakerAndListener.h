//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"

#include "DF_SpeakerAndListener.generated.h"

class UDF_Participant;
/**
 * A default implementation of the speakers and listeners in the dialogue node.
 * Useful when we have to display which participants are involved in the conversation.
 */
UCLASS(Category = "Joint|Native|Participant", DisplayName="Speaker And Listener")
class JOINTNATIVE_API UDF_SpeakerAndListener: public UDialogueFragment
{
	GENERATED_BODY()

public:

	UDF_SpeakerAndListener();

public:
	
	/**
	 * The array of the speakers in the dialogue.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Participant")
	TArray<FDialogueNodePointer> Speakers;
	
	/**
	 * The array of the Listeners in the dialogue.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Participant")
	TArray<FDialogueNodePointer> Listeners;
	
public:

	UFUNCTION(BlueprintCallable, Category="Participant")
	TArray<UDF_Participant*> GetAllSpeakers();

	UFUNCTION(BlueprintCallable, Category="Participant")
	TArray<UDF_Participant*> GetAllListeners();
	
};
