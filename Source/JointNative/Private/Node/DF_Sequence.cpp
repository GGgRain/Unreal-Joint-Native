//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Sequence.h"

#include "DialogueActor.h"

UDF_Sequence::UDF_Sequence()
{
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


void UDF_Sequence::OnNodeBeginPlay_Implementation()
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
