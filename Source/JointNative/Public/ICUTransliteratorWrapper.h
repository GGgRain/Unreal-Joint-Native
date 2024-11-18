// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ICUTransliteratorWrapper.generated.h"


//Added in Joint Native 1.4.0: Use it for the source files you want to use transliteration in, and wrap the codes in #if UE_ENABLE_ICU.

//Begin Macro of Forcing Compilation for ICU Transliteration (This works because it all happen in the linker)
/*
#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION 0
#include <iostream>
THIRD_PARTY_INCLUDES_START
#include <unicode/utrans.h>
#include <unicode/translit.h>
THIRD_PARTY_INCLUDES_END
#endif
*/

//End Macro of Forcing Compilation for ICU Transliteration (This works because it all happen in the linker)
/*
#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION SAVED_TRANSLITERATION
#undef SAVED_TRANSLITERATION
#endif
*/



#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION 0
#include <iostream>
THIRD_PARTY_INCLUDES_START
#include <unicode/translit.h>
#include <unicode/utrans.h>
THIRD_PARTY_INCLUDES_END
#endif


/**
 * UObject wrapper for the ICU transliterator object.
 */
UCLASS(Blueprintable,BlueprintType)
class JOINTNATIVE_API UICUTransliteratorWrapper : public UObject
{
	GENERATED_BODY()

public:

	UICUTransliteratorWrapper();

	~UICUTransliteratorWrapper();
	
public:

#if UE_ENABLE_ICU

	icu::Transliterator* TransliteratorInstance = nullptr;

#endif
	
	/**
	 * Transliterate strings from the start culture to most appropriate characters according to its pronounce in the destination culture. (e.g. 안녕하세요 -> annyeonghaseyo)
	 * You can test out the final result in this site : https://icu4c-demos.unicode.org/icu-bin/translit (ICU official)
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
	 * @return Transliterator wrapper object that contains the ICU native transliterator object.
	 */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Transliteration")
	FString TransliterateString(const FString Str);

public:
	
	/**
	 * Release transliterator instance.
	 */
	UFUNCTION(BlueprintCallable, Category="Transliteration")
	void ReleaseTransliterator();

	/**
	 * Create transliterator instance with the provided transform rule. check out possible rules for the system. https://icu4c-demos.unicode.org/icu-bin/translit (ICU official)
	 * @param TransformRule TransformRule for the transliterator.
	 */
	UFUNCTION(BlueprintCallable, Category="Transliteration")
	void CreateTransliterator(const FName TransformRule);
	
};

#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION SAVED_TRANSLITERATION
#undef SAVED_TRANSLITERATION
#endif
