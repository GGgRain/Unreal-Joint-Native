//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "JointNativeFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Component/DialogueParticipantComponent.h"

UDialogueParticipantComponent* UJointNativeFunctionLibrary::FindFirstParticipantComponent(
	UObject* WorldContextObject, FGameplayTag TargetParticipantTag)
{
	if (const UWorld* World = WorldContextObject->GetWorld())
	{
		for (TObjectIterator<UDialogueParticipantComponent> Itr; Itr; ++Itr)
		{
			if (Itr->GetWorld() != World) { continue; }

			if (Itr->ParticipantTag.HasTag(TargetParticipantTag)) return *Itr;
		}
	}

	return nullptr;
}

TArray<UDialogueParticipantComponent*> UJointNativeFunctionLibrary::FindParticipantComponents(
	UObject* WorldContextObject, FGameplayTag TargetParticipantTag)
{
	const UWorld* World = WorldContextObject->GetWorld();


	TArray<UDialogueParticipantComponent*> Comps;

	for (TObjectIterator<UDialogueParticipantComponent> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != World) continue;

		if (!Itr->ParticipantTag.HasTag(TargetParticipantTag)) continue;

		if (Comps.Contains(*Itr)) continue;

		Comps.Add(*Itr);
	}

	return Comps;
}

TArray<UDialogueParticipantComponent*> UJointNativeFunctionLibrary::GetAllParticipantComponents(
	UObject* WorldContextObject)
{
	const UWorld* World = WorldContextObject->GetWorld();

	TArray<UDialogueParticipantComponent*> Comps;

	for (TObjectIterator<UDialogueParticipantComponent> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != World) { continue; }

		if (Comps.Contains(*Itr)) { continue; }

		Comps.Add(*Itr);
	}

	return Comps;
}
