//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_SpeakerAndListener.generated.h"



/**
 * An interface class for the speaker andL listener nodes.
 * This has been added on Joint Native 1.13.0 update for the better support for the speaker and listener related fragment variations.
 * TODO: We aren't sure what else can be implemented as interfaces. Please let us know if you have any ideas, or suggestions!
 */

class UDF_Participant;

UINTERFACE(Blueprintable)
class JOINTNATIVE_API UJN_SpeakerAndListener_Interface : public UInterface
{
	GENERATED_BODY()
};

class JOINTNATIVE_API IJN_SpeakerAndListener_Interface
{
	GENERATED_BODY()

public:

	IJN_SpeakerAndListener_Interface() {}

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Speaker And Listener")
	TArray<UDF_Participant*> GetSpeakerParticipantList();

	virtual	TArray<UDF_Participant*> GetSpeakerParticipantList_Implementation() { return TArray<UDF_Participant*>(); }


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Speaker And Listener")
	TArray<UDF_Participant*> GetListenerParticipantList();

	virtual	TArray<UDF_Participant*> GetListenerParticipantList_Implementation() { return TArray<UDF_Participant*>(); }
	
};


/**
 * A default implementation of the speakers and listeners in the dialogue node.
 * Useful when we have to display which participants are involved in the conversation.
 */
UCLASS(Category = "Joint Native|Participant", DisplayName="Speaker And Listener")
class JOINTNATIVE_API UDF_SpeakerAndListener: public UJointFragment, public IJN_SpeakerAndListener_Interface
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
	TArray<UDF_Participant*> GetSpeakerParticipants() const;

	UFUNCTION(BlueprintPure, Category="Participant")
	TArray<UDF_Participant*> GetListenerParticipants() const;
	
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

public:

	virtual	TArray<UDF_Participant*> GetSpeakerParticipantList_Implementation() override;
	virtual	TArray<UDF_Participant*> GetListenerParticipantList_Implementation() override;

};
