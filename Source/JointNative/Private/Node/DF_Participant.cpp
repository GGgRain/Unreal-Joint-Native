//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Participant.h"

#include "JointNativeFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

UDF_Participant::UDF_Participant()
{
#if WITH_EDITORONLY_DATA
	// bUseSpecifiedGraphNodeBodyColor = true;
	// NodeBodyColor = FLinearColor(
	// 4.4f / 255.f,
	// 4.4f / 255.f,
	// 4.8f / 255.f,
	// 255.f / 255.f);
#endif
	
	SetReplicates(true);
	
}

void UDF_Participant::PostNodeBeginPlay_Implementation()
{
	if(!ParticipantComponentInstance && bAllowCollectingParticipantComponentOnWorldAutomatically)
	{
		ParticipantComponentInstance = UJointNativeFunctionLibrary::FindFirstParticipantComponent(GetWorld(),ParticipantTag);
	}
	
	Super::PostNodeBeginPlay_Implementation();
}

UDialogueParticipantComponent* UDF_Participant::GetParticipantComponent()
{
	return ParticipantComponentInstance;
}

void UDF_Participant::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	// Add properties to replicated for the derived class
	if(GetReplicates())
	{
		DOREPLIFETIME(UDF_Participant, ParticipantComponentInstance);
	}
}
