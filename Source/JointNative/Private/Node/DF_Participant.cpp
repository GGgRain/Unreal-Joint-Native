//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Participant.h"

#include "SubSystem/JointSubsystem.h"

UDF_Participant::UDF_Participant()
{

}

void UDF_Participant::OnNodeBeginPlay_Implementation()
{
	if(!ParticipantComponentInstance && bAllowCollectingParticipantComponentOnWorldAutomatically)
	{
		ParticipantComponentInstance = UJointSubsystem::FindFirstParticipantComponent(GetWorld(),ParticipantTag);
	}
	
	Super::OnNodeBeginPlay_Implementation();
}

UDialogueParticipantComponent* UDF_Participant::GetParticipantComponent()
{
	return ParticipantComponentInstance;
}
