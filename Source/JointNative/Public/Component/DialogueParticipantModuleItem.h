// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueParticipantModuleItem.generated.h"

/**
 * A module item that will be attached to the Dialogue Participant Module. Inherit this class to implement additional functionalities for the dialogue participants.
 *
 * This is introduced and will be the second track, to make the actors more lightweight and modular, because attaching a bunch of components to the actor can be problematic.
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced, Abstract, meta=(DisplayName="Dialogue Participant Module Item"))
class JOINTNATIVE_API UDialogueParticipantModuleItem : public UObject
{
	GENERATED_BODY()
	
};
