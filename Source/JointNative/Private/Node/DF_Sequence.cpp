//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Sequence.h"

#include "DialogueActor.h"

UDF_Sequence::UDF_Sequence()
{

#if WITH_EDITORONLY_DATA

	// bUseSpecifiedGraphNodeBodyColor = true;
	// NodeBodyColor = FLinearColor(
	// 	2.4f / 255.f,
	// 	2.4f / 255.f,
	// 	2.9f / 255.f,
	// 	225.f / 255.f);
	DefaultEdSlateDetailLevel = EDialogueEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;

#endif
	
}

void UDF_Sequence::SelectNodeAsPlayingNode(UDialogueNodeBase* SubNode)
{
	SubNode->OnDialogueNodeMarkedAsPendingDelegate.AddDynamic(this, &UDF_Sequence::OnSubNodePending);

	GetHostingDialogueInstance()->RequestNodeBeginPlay(SubNode);
}

void UDF_Sequence::PlayNextSubNode()
{
	if (!GetHostingDialogueInstance().IsValid()) return;

	CurrentIndex++;

	while (SubNodes.IsValidIndex(CurrentIndex))
	{
		UDialogueNodeBase* SubNode = SubNodes[CurrentIndex];

		if (SubNode != nullptr)
		{
			SelectNodeAsPlayingNode(SubNode);

			break;
		}

		CurrentIndex++;
	}


	if (!SubNodes.IsValidIndex(CurrentIndex))
	{
		GetHostingDialogueInstance()->RequestNodeEndPlay(this);
	}
}


void UDF_Sequence::PostNodeBeginPlay_Implementation()
{
	//reset
	CurrentIndex = INDEX_NONE;
	
	PlayNextSubNode();
}

void UDF_Sequence::OnSubNodePending(UDialogueNodeBase* InNode)
{
	if (InNode == nullptr) return;

	InNode->OnDialogueNodeMarkedAsPendingDelegate.RemoveDynamic(this, &UDF_Sequence::OnSubNodePending);

	PlayNextSubNode();
}
