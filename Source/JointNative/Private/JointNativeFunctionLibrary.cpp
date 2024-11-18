//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "JointNativeFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "ICUTransliteratorWrapper.h"
#include "Component/DialogueParticipantComponent.h"
#include "Kismet/GameplayStatics.h"

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


void UJointNativeFunctionLibrary::ProjectWorldPositionToScreenPosition(const UObject* WorldContextObject,
                                                                       const FVector& InWorldPosition,
                                                                       FVector2D& ScreenPos)
{
	FVector Projected;

	bool bTargetBehindCamera = false;

	// Custom Projection Function
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		ULocalPlayer* const Player = PlayerController->GetLocalPlayer();

		if (Player && Player->ViewportClient)
		{
			FSceneViewProjectionData NewProjectionData;

			if (Player->GetProjectionData(Player->ViewportClient->Viewport, NewProjectionData))
			{
				const FMatrix ViewProjectionMatrix = NewProjectionData.ComputeViewProjectionMatrix();
				const FIntRect ViewRectangle = NewProjectionData.GetConstrainedViewRect();

				FPlane Result = ViewProjectionMatrix.TransformFVector4(FVector4(InWorldPosition, 1.f));
				if (Result.W < 0.f) { bTargetBehindCamera = true; }
				if (Result.W == 0.f) { Result.W = 1.f; } // Prevent Divide By Zero

				const float RHW = 1.f / FMath::Abs(Result.W);
				Projected = FVector(Result.X, Result.Y, Result.Z) * RHW;

				// Normalize to 0..1 UI Space
				const float NormX = (Projected.X / 2.f) + 0.5f;
				const float NormY = 1.f - (Projected.Y / 2.f) - 0.5f;

				Projected.X = static_cast<float>(ViewRectangle.Min.X) + NormX * static_cast<float>(ViewRectangle.
					Width());
				Projected.Y = static_cast<float>(ViewRectangle.Min.Y) + NormY * static_cast<float>(ViewRectangle.
					Height());

				if (bTargetBehindCamera)
				{
					const FVector2D ScreenSize = FVector2D(static_cast<float>(ViewRectangle.Width()),
					                                       static_cast<float>(ViewRectangle.Height()));

					FVector2D NewProjected = FVector2D(Projected.X, Projected.Y) - ScreenSize * 0.5;

					NewProjected.Normalize();

					NewProjected *= ScreenSize.Size() * 0.5;

					NewProjected += ScreenSize * 0.5;

					NewProjected.X = FMath::Clamp(NewProjected.X, 0, ScreenSize.X);
					NewProjected.Y = FMath::Clamp(NewProjected.Y, 0, ScreenSize.Y);

					Projected.X = NewProjected.X;
					Projected.Y = NewProjected.Y;
				}
			}
		}
	}

	ScreenPos = FVector2D(Projected.X, Projected.Y);
}

UICUTransliteratorWrapper* UJointNativeFunctionLibrary::CreateTransliterator(const FName TransformRule = FName("Any-Latin"))
{
	UICUTransliteratorWrapper* ICUTransliteratorWrapper = NewObject<UICUTransliteratorWrapper>(
		UJointNativeFunctionLibrary::GetInstance());

	if(ICUTransliteratorWrapper) {
		ICUTransliteratorWrapper->CreateTransliterator(TransformRule);
	}

	return ICUTransliteratorWrapper;
}

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


FString UJointNativeFunctionLibrary::PrintTransliterationIDs(const bool bPrintOnScreen = true, const bool bPrintOnLog = true)
{

	FString ReturnString = "ICU data are not available. Please check out the settings.";
	
#if UE_ENABLE_ICU
	
	FString IDString = "Available ID : ";
	
	const int IDCount = icu::Transliterator::countAvailableIDs();
	
	for(int Index = 0 ; Index < IDCount; Index++)
	{
		if(Index != 0) IDString.Append(", ");
		
		icu::UnicodeString CurIDString = icu::Transliterator::getAvailableID(Index);

		std::string ConvertStr;
		CurIDString.toUTF8String(ConvertStr);

		IDString.Append(FString(ConvertStr.c_str()));
		
	}

	ReturnString = IDString;
	
#endif

#if UE_BUILD_DEBUG

	if(bPrintOnScreen)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Yellow,
				TEXT("UJointNativeFunctionLibrary : %s"), *ReturnString );
	}

	if(bPrintOnLog)
	{
		UE_LOG(LogTemp,Log,TEXT("UJointNativeFunctionLibrary : %s"), *ReturnString)
	}
	
#endif
	
	return ReturnString;
}


#if UE_ENABLE_ICU
#define SAVED_TRANSLITERATION UCONFIG_NO_TRANSLITERATION
#undef UCONFIG_NO_TRANSLITERATION
#define UCONFIG_NO_TRANSLITERATION SAVED_TRANSLITERATION
#undef SAVED_TRANSLITERATION
#endif
