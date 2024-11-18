// Fill out your copyright notice in the Description page of Project Settings.


#include "ICUTransliteratorWrapper.h"


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


UICUTransliteratorWrapper::UICUTransliteratorWrapper()
{
	//empty, for the explicit decl
}

UICUTransliteratorWrapper::~UICUTransliteratorWrapper()
{
	ReleaseTransliterator();
}


void UICUTransliteratorWrapper::ReleaseTransliterator()
{
#if UE_ENABLE_ICU

	if (TransliteratorInstance != nullptr)
	{
		icu::Transliterator::unregister(TransliteratorInstance->getID());

		if (TransliteratorInstance)
		{
			delete TransliteratorInstance;
		}
		
		TransliteratorInstance = nullptr;
	}

#endif
}

void UICUTransliteratorWrapper::CreateTransliterator(const FName TransformRule)
{
	
#if UE_ENABLE_ICU

	if (TransliteratorInstance != nullptr)
	{
#if UE_BUILD_DEBUG
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("UJointNativeFunctionLibrary : Failed to create a ICU transliterator, It already had a transliterator instance. Please clear the instance first.") );	
#endif
	}

	const icu::UnicodeString RuleString(*TransformRule.ToString());

	UErrorCode Status = U_ZERO_ERROR;

	TransliteratorInstance = icu::Transliterator::createInstance(RuleString, UTRANS_FORWARD, Status);
	
	if (TransliteratorInstance == nullptr)
	{
#if UE_BUILD_DEBUG
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("UJointNativeFunctionLibrary : Failed to create a ICU transliterator, Error code : %d.\nPlease change 'Internationalization Support' under project settings > packaging to include the localization data for the languages if you want to use transliteration or ICU code on the final build.\nIf this message still be displayed after you included localization data, please report this to the creator of the plugin."), Status);	
#endif
	}

#endif
}


FString UICUTransliteratorWrapper::TransliterateString(const FString Str)
{
	FString OutString = Str;

#if UE_ENABLE_ICU

	if (TransliteratorInstance == nullptr) return OutString;

	icu::UnicodeString Output = icu::UnicodeString(*Str);

	TransliteratorInstance->transliterate(Output);

	std::string ConvertStr;
	Output.toUTF8String(ConvertStr);

	OutString = FString(ConvertStr.c_str());

#endif

	return OutString;
}


#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION SAVED_TRANSLITERATION
#undef SAVED_TRANSLITERATION
#endif
