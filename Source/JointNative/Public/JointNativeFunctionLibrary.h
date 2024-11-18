//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JointNativeFunctionLibrary.generated.h"

class UWidget;
class UICUTransliteratorWrapper;

/**
 * Joint Native's BP function library that helps you to do everything in BP side without messing with the crazy c++.
 * This class involves about querying, widget screen projection (advanced) , ICU related features (transliteration)
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

public:
	
	UFUNCTION(BlueprintCallable, Category = "Projection", meta=(WorldContext="WorldContextObject"))
	static void ProjectWorldPositionToScreenPosition(
		const UObject* WorldContextObject,
		const FVector& InWorldPosition,
		FVector2D& ScreenPos
	);

public:


	/**
	 * Create a transliterator with the provided destination and start culture.
	 * It will transliterate strings from the start culture to most appropriate characters according to its pronounce in the destination culture. (e.g. 안녕하세요 -> annyeonghaseyo)
	 * You can test out the final result in this site : https://icu4c-demos.unicode.org/icu-bin/translit (ICU official)
	 *
	 * Transliteration will work only in the packaged build. (Will not work as intended on the editor)
	 * This feature requires the project to contain ICU culture-specific data on its package to work properly. Please change 'Internationalization Support' under project settings > packaging to include the culture-specific data for the languages if you want to use transliteration or ICU code on the final build.
	 * Here is the size of each of the culture-specific data :
	 * 
	 * English (~1.77MB)
	 * EFIGS (~2.38MB)
	 * EFIGSCJK (~5.99MB)
	 * CJK (~5.16MB)
	 * All (~15.3MB)
	 *
	 * @param TransformRule Transform rule for the transliterator. check out possible rules for the system. https://icu4c-demos.unicode.org/icu-bin/translit (ICU official)
	 * @return Transliterator wrapper object that contains the ICU native transliterator object.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Transliteration")
	static UICUTransliteratorWrapper* CreateTransliterator(const FName TransformRule);

	/**
	 * Print the list of possible cultures that can be used on the transliteration. It can be changed from each stage of the project and project settings, so please check this out before you proceed to publish it.
	 * @return log for the ids.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Transliteration")
	static FString PrintTransliterationIDs(const bool bPrintOnScreen, const bool bPrintOnLog);

public:
	
	//C++ only function that gets the CDO object for the library class.
	static UJointNativeFunctionLibrary* GetInstance() { return StaticClass()->GetDefaultObject<UJointNativeFunctionLibrary>();}
	
};
