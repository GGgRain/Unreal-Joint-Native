//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "Component/DialogueParticipantComponent.h"

#include "GameFramework/Actor.h"
#include "Component/DialogueParticipantModuleItem.h"
#include "Engine/ActorChannel.h"
#include "Misc/EngineVersionComparison.h"
#include "Net/UnrealNetwork.h"

// Define to use new replication system introduced in UE 5.1.0.
#define USE_NEW_REPLICATION !UE_VERSION_OLDER_THAN(5, 1, 0) && true


// Sets default values for this component's properties
UDialogueParticipantComponent::UDialogueParticipantComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(bShouldStartReplicatesOnInitialization);
	
}

UDialogueParticipantModuleItem* UDialogueParticipantComponent::GetParticipantModuleByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass) const
{
	for (UDialogueParticipantModuleItem* ModuleItem : ParticipantModules)
	{
		if (ModuleItem && ModuleItem->IsA(ModuleClass))
		{
			return ModuleItem;
		}
	}
	
	return nullptr;
}

TArray<UDialogueParticipantModuleItem*> UDialogueParticipantComponent::GetParticipantModulesByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass) const
{
	TArray<UDialogueParticipantModuleItem*> Modules;

	for (UDialogueParticipantModuleItem* ModuleItem : ParticipantModules)
	{
		if (ModuleItem && ModuleItem->IsA(ModuleClass))
		{
			Modules.Add(ModuleItem);
		}
	}
	
	return Modules;
}

UDialogueParticipantModuleItem* UDialogueParticipantComponent::AddParticipantModuleByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass)
{
	if (!ModuleClass) return nullptr;

	UDialogueParticipantModuleItem* NewModule = NewObject<UDialogueParticipantModuleItem>(this, ModuleClass);
	
	if (NewModule)
	{
		ParticipantModules.Add(NewModule);
		
		// If the module is set to replicate, add it to the networking cache.
		if (NewModule->GetReplicates())
		{
			AddModuleForNetworking(NewModule);
		}
	}

	return NewModule;
}

void UDialogueParticipantComponent::RemoveParticipantModule(UDialogueParticipantModuleItem* ModuleToRemove)
{
	if (!ModuleToRemove) return;

	if (ParticipantModules.Remove(ModuleToRemove) > 0)
	{
		// If the module is set to replicate, remove it from the networking cache.
		if (ModuleToRemove->GetReplicates())
		{
			RemoveModuleForNetworking(ModuleToRemove);
		}
	}
}

void UDialogueParticipantComponent::OnRep_CachedParticipantModulesForNetworking(const TArray<UDialogueParticipantModuleItem*>& PreviousCache)
{
	// ATM, CachedAllNodesForNetworking is already updated with the new value when this function is called - so we can compare it with the previous value.
	
#if USE_NEW_REPLICATION
	
	if (IsUsingRegisteredSubObjectList())
	{
		// Find the attributes that got removed
		for (UDialogueParticipantModuleItem* PreviousObj : PreviousCache)
		{
			if (PreviousObj)
			{
				const bool bWasRemoved = CachedParticipantModulesForNetworking.Find(PreviousObj) == INDEX_NONE;
				
				if (bWasRemoved)
				{
					RemoveReplicatedSubObject(PreviousObj);
				}
			}
		}

		// Find the attributes that got added
		for (UDialogueParticipantModuleItem* CurObj : CachedParticipantModulesForNetworking)
		{
			if (IsValid(CurObj))
			{
				const bool bIsAdded = PreviousCache.Find(CurObj) == INDEX_NONE;
				
				if (bIsAdded)
				{
					AddReplicatedSubObject(CurObj);
				}
			}
		}
	}
	
#endif
}

void UDialogueParticipantComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params;
	Params.bIsPushBased = true;

	Params.Condition = COND_None;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDialogueParticipantComponent, CachedParticipantModulesForNetworking, Params);
	//DOREPLIFETIME(AJointActor, JointManager);
}

bool UDialogueParticipantComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	
#if USE_NEW_REPLICATION
	
	return Super::ReplicateSubobjects(Channel,Bunch,RepFlags);

#else


	check(Channel);
	check(Bunch);
	check(RepFlags);

	bool WroteSomething = false;


	for (UDialogueParticipantModuleItem* ModuleForNetworking : CachedParticipantModulesForNetworking)
	{
		if (IsValid(ModuleForNetworking))
		{
			WroteSomething |= Channel->ReplicateSubobject(ModuleForNetworking, *Bunch, *RepFlags);
		}
	}
	
	/**
		//we do nothing for the other components for now.
		for (UActorComponent* ActorComp : ReplicatedComponents)
		{
			if (ActorComp && ActorComp->GetIsReplicated())
			{
				WroteSomething |= ActorComp->ReplicateSubobjects(Channel, Bunch, RepFlags);
				// Lets the component add subobjects before replicating its own properties.
				WroteSomething |= Channel->ReplicateSubobject(ActorComp, *Bunch, *RepFlags);
				// (this makes those subobjects 'supported', and from here on those objects may have reference replicated)		
			}
		}
	 */	
	
	return WroteSomething;

#endif
}

void UDialogueParticipantComponent::CacheNodesForNetworking()
{
	// This function should be called only on the authority side.
	if (GetOwner() && GetOwner()->HasAuthority())
	{
#if USE_NEW_REPLICATION
		
		for (TObjectPtr<UDialogueParticipantModuleItem>& ParticipantModulesForNetworking : CachedParticipantModulesForNetworking)
		{
			if(IsValid(ParticipantModulesForNetworking))
			{
				RemoveModuleForNetworking(ParticipantModulesForNetworking);
			}
		}
		
#endif
		
		CachedParticipantModulesForNetworking.Empty();

		TArray<UDialogueParticipantModuleItem*> Modules;

		for (TObjectPtr<UDialogueParticipantModuleItem>& DialogueParticipantModuleItem : ParticipantModules)
		{
			if (IsValid(DialogueParticipantModuleItem))
			{
				if (DialogueParticipantModuleItem->GetReplicates())
				{
					Modules.Add(DialogueParticipantModuleItem);
				}
			}
		}
		
		CachedParticipantModulesForNetworking = Modules;
		
#if USE_NEW_REPLICATION
		
		// This must be called after the caching

		for (TObjectPtr<UDialogueParticipantModuleItem>& ParticipantModulesForNetworking : CachedParticipantModulesForNetworking)
		{
			if(IsValid(ParticipantModulesForNetworking))
			{
				AddReplicatedSubObject(ParticipantModulesForNetworking);
			}
		}

#endif
		
	}
}

void UDialogueParticipantComponent::AddModuleForNetworking(class UDialogueParticipantModuleItem* InModule)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (CachedParticipantModulesForNetworking.Contains(InModule)) return;

#if USE_NEW_REPLICATION
	
		AddReplicatedSubObject(InModule);

#endif

		CachedParticipantModulesForNetworking.Add(InModule);
	}
}

void UDialogueParticipantComponent::RemoveModuleForNetworking(class UDialogueParticipantModuleItem* InModule)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (!CachedParticipantModulesForNetworking.Contains(InModule)) return;

#if USE_NEW_REPLICATION
	
		RemoveReplicatedSubObject(InModule);

#endif

		CachedParticipantModulesForNetworking.Remove(InModule);
	}
}




#undef USE_NEW_REPLICATION
