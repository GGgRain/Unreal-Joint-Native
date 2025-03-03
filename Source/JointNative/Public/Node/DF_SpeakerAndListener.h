//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_SpeakerAndListener.generated.h"



class UDF_Participant;
/**
 * A default implementation of the speakers and listeners in the dialogue node.
 * Useful when we have to display which participants are involved in the conversation.
 */
UCLASS(Category = "Joint Native|C++|Participant", DisplayName="Speaker And Listener")
class JOINTNATIVE_API UDF_SpeakerAndListener: public UJointFragment
{
	GENERATED_BODY()

public:

	UDF_SpeakerAndListener();

	
	/**
	 * The array of the speakers in the dialogue.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Participant")
	TArray<FJointNodePointer> Speakers;
	
	/**
	 * The array of the Listeners in the dialogue.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Participant")
	TArray<FJointNodePointer> Listeners;

public:

	UFUNCTION(BlueprintPure, Category="Participant")
	TArray<UDF_Participant*> GetSpeakerParticipants();

	UFUNCTION(BlueprintPure, Category="Participant")
	TArray<UDF_Participant*> GetListenerParticipants();
	
public:

	UFUNCTION(BlueprintPure, Category="Participant")
	TArray<FJointNodePointer> GetSpeakers();

	UFUNCTION(BlueprintPure, Category="Participant")
	TArray<FJointNodePointer> GetListeners();

public:

	UFUNCTION(BlueprintCallable, Category="Participant")
	void SetSpeakers(TArray<FJointNodePointer> InSpeakers);

	UFUNCTION(BlueprintCallable, Category="Participant")
	void SetListeners(TArray<FJointNodePointer> InListeners);

};
