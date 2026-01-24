// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DialogueParticipantModuleItem.h"

#include "Component/DialogueParticipantComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/NetDriver.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Kismet/GameplayStatics.h"

UDialogueParticipantModuleItem::UDialogueParticipantModuleItem()
{
	
}

UWorld* UDialogueParticipantModuleItem::GetWorld() const
{
	if (GetParticipantComponent()) return GetParticipantComponent()->GetWorld();

	return nullptr;
}

class UDialogueParticipantComponent* UDialogueParticipantModuleItem::GetParticipantComponent() const
{
	UObject* Outer = GetOuter();
	
	return Outer ? Cast<UDialogueParticipantComponent>(Outer) : nullptr;
}

void UDialogueParticipantModuleItem::SetReplicates_Implementation(const bool bNewReplicates)
{
	if (bReplicates != bNewReplicates)
	{
		if(GetParticipantComponent())
		{
			if(bNewReplicates)
			{
				GetParticipantComponent()->AddModuleForNetworking(this);
			}else
			{
				GetParticipantComponent()->RemoveModuleForNetworking(this);
			}
		}

		bReplicates = bNewReplicates;
	}
}

const bool UDialogueParticipantModuleItem::GetReplicates() const
{
	return bReplicates;
}

bool UDialogueParticipantModuleItem::IsSupportedForNetworking() const
{
	return true;
}

void UDialogueParticipantModuleItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	if (const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass()))
	{
		BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}
}

bool UDialogueParticipantModuleItem::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	
	UDialogueParticipantComponent* ParticipantComp = GetParticipantComponent();
	AActor* OwnerActor = ParticipantComp ? ParticipantComp->GetOwner() : nullptr;
	if (!ParticipantComp || !OwnerActor) return false;
	
	/**
	 * If bUsePlayerControllerAsRPCFunctionCallspace is true and the client does not have authority over the Joint Instance, it will try to retrieve the PlayerController's NetDriver to process the remote function.
	 * + This is extremely experimental.
	 */
	
	if (!OwnerActor->HasAuthority() && bUsePlayerControllerAsRPCFunctionCallspace)
	{
		//Use the PlayerController's function callspace.
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (!PC) return false;

		UNetDriver* NetDriver = PC->GetNetDriver();
	
		if (!NetDriver) return false;

		NetDriver->ProcessRemoteFunction(PC, Function, Parms, OutParms, Stack, this);
	}
	
	
	//Use the Joint actor's function callspace instead.
	UNetDriver* NetDriver = OwnerActor->GetNetDriver();
	
	if (!NetDriver) return false;

	NetDriver->ProcessRemoteFunction(OwnerActor, Function, Parms, OutParms, Stack, this);
	
	return true;
}

int32 UDialogueParticipantModuleItem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	UDialogueParticipantComponent* ParticipantComp = GetParticipantComponent();
	AActor* OwnerActor = ParticipantComp ? ParticipantComp->GetOwner() : nullptr;
	
	if (!ParticipantComp || !OwnerActor) return false;
	
#if WITH_EDITOR
	
	if (HasAnyFlags(RF_ClassDefaultObject) || !IsSupportedForNetworking() || OwnerActor == nullptr)
	{
		// This handles absorbing authority/cosmetic
		return GEngine->GetGlobalFunctionCallspace(Function, this, Stack);
	}
	
	//for the clients that do not have authority (over the Joint Instance) - use the player controller's function callspace if the option is enabled.
	if (!OwnerActor->HasAuthority() && bUsePlayerControllerAsRPCFunctionCallspace)
	{
		//Use the PlayerController's function callspace.
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		if (PC)
		{
			return PC->GetFunctionCallspace(Function, Stack);
		}
	}
	
	return OwnerActor->GetFunctionCallspace(Function, Stack);

#else

	if (HasAnyFlags(RF_ClassDefaultObject) || !IsSupportedForNetworking() || OwnerActor == nullptr)
	{
		// This handles absorbing authority/cosmetic
		return GEngine->GetGlobalFunctionCallspace(Function, this, Stack);
	}

	//for the clients that do not have authority (over the Joint Instance) - use the player controller's function callspace if the option is enabled.
	if (!OwnerActor->HasAuthority() && bUsePlayerControllerAsRPCFunctionCallspace)
	{
		//Use the PlayerController's function callspace.
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		if (PC)
		{
			return PC->GetFunctionCallspace(Function, Stack);
		}
	}
	
	return OwnerActor->GetFunctionCallspace(Function, Stack);
	
#endif
	
	
}