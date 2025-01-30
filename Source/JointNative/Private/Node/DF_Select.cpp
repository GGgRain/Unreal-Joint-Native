//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DF_Select.h"
#include "DialogueActor.h"

UDF_Select::UDF_Select()
{

#if WITH_EDITORONLY_DATA

	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.4f, 0.2f, 0.5f, 0.400000);
	DefaultEdSlateDetailLevel = EDialogueEdSlateDetailLevel::SlateDetailLevel_Stow;


#endif
	
}

void UDF_Select::PostNodeBeginPlay_Implementation()
{
	bIsSelected = false;
	
	Super::PreNodeBeginPlay_Implementation();
}

TArray<UDialogueNodeBase*> UDF_Select::SelectNextNodes_Implementation(
	const TSoftObjectPtr<ADialogueActor>& InHostingDialogueInstance)
{
	return bIsSelected ? NextNodes : TArray<UDialogueNodeBase*>();
}

bool UDF_Select::GetSelected() const
{
	return bIsSelected;
}

void UDF_Select::SetSelected(const bool bNewSelected)
{
	const bool LastSelection = bIsSelected;
	
	bIsSelected = bNewSelected;

	if(LastSelection != bNewSelected)
	{
		if(OnSelectionChanged.IsBound())
		{
			OnSelectionChanged.Broadcast(this, bNewSelected);
		}
	}
}

#undef LOCTEXT_NAMESPACE