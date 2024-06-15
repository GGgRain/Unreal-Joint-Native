//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JointNativeFunctionLibrary.generated.h"

class UWidget;
/**
 * 
 */
UCLASS()
class JOINTNATIVE_API UJointNativeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Find and return the first search result of the dialogue handle for the given participant tag.
	 * @param WorldContextObject An object that this function will grab the world from. You can provide the subsystem itself. (In Blueprint, it will be automatically filled out.)
	 * @param TargetParticipantTag The participant tag to look for.
	 * @return Found participant component. nullptr if not present.
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue", meta=(WorldContext="WorldContextObject"))
	static class UDialogueParticipantComponent* FindFirstParticipantComponent(
		UObject* WorldContextObject,
		FGameplayTag TargetParticipantTag
	);
	
	/**
	 * Find and return all the dialogue handles for the given participant tag.
	 * @param WorldContextObject An object that this function will grab the world from. You can provide the subsystem itself. (In Blueprint, it will be automatically filled out.)
	 * @param TargetParticipantTag The participant tag to look for
	 * @return An array of found participant components.
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue", meta=(WorldContext="WorldContextObject"))
	static TArray<class UDialogueParticipantComponent*> FindParticipantComponents(
		UObject* WorldContextObject,
		FGameplayTag TargetParticipantTag
	);

	/**
	 * Get all the participant components in the world.
	 * @param WorldContextObject An object that this function will grab the world from. You can provide the subsystem itself. (In Blueprint, it will be automatically filled out.)
	 * @return An array of found participant components.
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue", meta=(WorldContext="WorldContextObject"))
	static TArray<class UDialogueParticipantComponent*> GetAllParticipantComponents(
		UObject* WorldContextObject
	);
	
};
