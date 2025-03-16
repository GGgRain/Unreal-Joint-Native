//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DialogueParticipantComponent.generated.h"

class UDialogueParticipantModuleItem;
class UJointManager;

/**
 * Important Note for the all users and SDS1 users.
 * Additional functionalities must be implemented with additional components.
 * Just like the notch component does.
 * Now DialogueParticipantComponent only handle the identification of the participants in the dialogue.
 */

UCLASS( ClassGroup=("Dialogue"), meta = (BlueprintSpawnableComponent))
class JOINTNATIVE_API UDialogueParticipantComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UDialogueParticipantComponent();
	
public:

	/**
	 * Important Note for the all users and SDS1 users.
	 * Additional functionalities must be implemented with additional components.
	 * Just like the notch component does.
	 * Now DialogueParticipantComponent only handle the identification of the participants in the dialogue.
	 */
	
public:

	/**
	 * Tag of this participant that will be used on the dialogue.
	 * You can access this component in the dialogue by searching it with its ParticipantTag.
	 * Note for the SDS1 users : it's a new version of IDName in SDS2.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble")
		FGameplayTagContainer ParticipantTag;

public:

	/**
	 * Module items that will be attached to the Dialogue Participant Modules.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble")
	TArray<TObjectPtr<class UDialogueParticipantModuleItem>> ParticipantModules;
	
};
