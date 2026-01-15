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
	
public:
	
	UDialogueParticipantModuleItem();
	
public:
	
	//Grab the world object reference from the Joint instance and return it.
	virtual UWorld* GetWorld() const override;

public:
	
	/**
	 * Get the participant component that is owning this module item.
	 */
	UFUNCTION(BlueprintPure, Category="Dialogue Participant Module Item")
	class UDialogueParticipantComponent* GetParticipantComponent() const;

private:
	
	//Networking & RPC related.

	/**
	 * Whether this node replicates through the network. This variable must be true to replicate any property with this node.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Networking")
	bool bReplicates = false;
	
	/**
	 * Whether to use the player controller's function callspace for the RPC function calls.
	 * This allows the RPC functions to be executed without implementing workaround functions on the controller side.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Networking|Advanced (Experimental)")
	bool bUsePlayerControllerAsRPCFunctionCallspace = false;

public:
	
	/**
	 * Set whether to replicate the node.
	 */
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category="Networking")
	void SetReplicates(const bool bNewReplicates);
	void SetReplicates_Implementation(const bool bNewReplicates);
	
	/**
	 * Set whether to replicate the node.
	 */
	UFUNCTION(BlueprintPure, Category="Networking")
	const bool GetReplicates() const;
	
public:
	
	virtual bool IsSupportedForNetworking() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override;

	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	
};
