//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Participant.h"

#include "JointNativeFunctionLibrary.h"

UDF_Participant::UDF_Participant()
{
	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(
	4.4f / 255.f,
	4.4f / 255.f,
	4.8f / 255.f,
	255.f / 255.f);
}

void UDF_Participant::OnNodeBeginPlay_Implementation()
{
	if(!ParticipantComponentInstance && bAllowCollectingParticipantComponentOnWorldAutomatically)
	{
		ParticipantComponentInstance = UJointNativeFunctionLibrary::FindFirstParticipantComponent(GetWorld(),ParticipantTag);
	}
	
	Super::OnNodeBeginPlay_Implementation();
}

UDialogueParticipantComponent* UDF_Participant::GetParticipantComponent()
{
	return ParticipantComponentInstance;
}
