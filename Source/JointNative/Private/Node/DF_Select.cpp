//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DF_Select.h"
#include "DialogueActor.h"

UDF_Select::UDF_Select()
{
	
}

void UDF_Select::OnNodeBeginPlay_Implementation()
{
	bIsSelected = false;
	
	Super::OnNodeBeginPlay_Implementation();
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