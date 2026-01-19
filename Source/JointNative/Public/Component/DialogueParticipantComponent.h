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
	 * Joint Native 1.16: Now supports replication.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble")
	TArray<TObjectPtr<UDialogueParticipantModuleItem>> ParticipantModules;
	
	
public:
	
	/**
	 * Get a participant module by class.
	 * @param ModuleClass The module class to search.
	 */
	UFUNCTION(BlueprintPure, Category="Dialogue Participant Component", meta=(DeterminesOutputType="ModuleClass"))
	UDialogueParticipantModuleItem* GetParticipantModuleByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass) const;

	/**
	 * Get all participant modules by class.
	 * @param ModuleClass The module class to search.
	 */
	UFUNCTION(BlueprintPure, Category="Dialogue Participant Component", meta=(DeterminesOutputType="ModuleClass"))
	TArray<UDialogueParticipantModuleItem*> GetParticipantModulesByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass) const;
	
	/**
	 * Add a new participant module by class. (it will not be replicated if you add it on the client side. You have to add it on the server side to replicate it properly)
	 * @param ModuleClass The module class to add.
	 */
	UFUNCTION(BlueprintCallable, Category="Dialogue Participant Component", meta=(DeterminesOutputType="ModuleClass"))
	UDialogueParticipantModuleItem* AddParticipantModuleByClass(TSubclassOf<UDialogueParticipantModuleItem> ModuleClass);

	/**
	 * Remove a participant module.
	 * @param ModuleToRemove The module instance to remove.
	 */
	UFUNCTION(BlueprintCallable, Category="Dialogue Participant Component")
	void RemoveParticipantModule(UDialogueParticipantModuleItem* ModuleToRemove);
	
public:

	/**
	 * whether to start replication of the participant modules on the initialization.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Dialogue Participant Component")
	bool bShouldStartReplicatesOnInitialization = true;
	
private:
	
	/**
	 * Cached Joint nodes for the replication.
	 */
	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_CachedParticipantModulesForNetworking)
	TArray<TObjectPtr<UDialogueParticipantModuleItem>> CachedParticipantModulesForNetworking;

	UFUNCTION()
	void OnRep_CachedParticipantModulesForNetworking(const TArray<UDialogueParticipantModuleItem*>& PreviousCache);
	
private:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

private:

	//Don't call this in out of initialization.
	void CacheNodesForNetworking();

public:

	void AddModuleForNetworking(class UDialogueParticipantModuleItem* InModule);
	
	void RemoveModuleForNetworking(class UDialogueParticipantModuleItem* InModule);
	
};
