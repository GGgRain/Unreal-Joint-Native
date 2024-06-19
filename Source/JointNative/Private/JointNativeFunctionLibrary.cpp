//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "JointNativeFunctionLibrary.h"
#include "GameplayTagContainer.h"
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



void UJointNativeFunctionLibrary::ProjectWorldPositionToScreenPosition(const UObject* WorldContextObject, const FVector& InWorldPosition, FVector2D& ScreenPos)
{
	FVector Projected;
	
	bool bTargetBehindCamera = false;

	// Custom Projection Function
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
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
 
				Projected.X = static_cast<float>(ViewRectangle.Min.X) + NormX * static_cast<float>(ViewRectangle.Width());
				Projected.Y = static_cast<float>(ViewRectangle.Min.Y) + NormY * static_cast<float>(ViewRectangle.Height());

				if(bTargetBehindCamera)
				{

					const FVector2D ScreenSize = FVector2D(static_cast<float>(ViewRectangle.Width()), static_cast<float>(ViewRectangle.Height()));
						
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

