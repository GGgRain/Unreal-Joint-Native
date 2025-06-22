//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "Node/DF_Select.h"

#include "JointActor.h"
#include "JointVersionComparison.h"

UDF_Select::UDF_Select()
{

#if WITH_EDITORONLY_DATA

#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.4f * 0.7, 0.2f * 0.7, 0.5f * 0.7, 0.400000);
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Stow;
	
#else

	EdNodeSetting.bUseSpecifiedGraphNodeBodyColor = true;
	EdNodeSetting.NodeBodyColor = FLinearColor(0.4f * 0.7, 0.2f * 0.7, 0.5f * 0.7, 0.400000);
	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Stow;
	
#endif
	
#endif

	
}

void UDF_Select::PostNodeBeginPlay_Implementation()
{
	bIsSelected = false;
	
	Super::PreNodeBeginPlay_Implementation();
}

TArray<UJointNodeBase*> UDF_Select::SelectNextNodes_Implementation(
	AJointActor* InHostingDialogueInstance)
{
	return bIsSelected ? NextNodes : TArray<UJointNodeBase*>();
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