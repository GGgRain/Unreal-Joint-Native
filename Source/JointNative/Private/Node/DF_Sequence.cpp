//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Sequence.h"

#include "JointActor.h"

UDF_Sequence::UDF_Sequence()
{

#if WITH_EDITORONLY_DATA

	// bUseSpecifiedGraphNodeBodyColor = true;
	// NodeBodyColor = FLinearColor(
	// 	2.4f / 255.f,
	// 	2.4f / 255.f,
	// 	2.9f / 255.f,
	// 	225.f / 255.f);
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;

#endif
	
}

void UDF_Sequence::SelectNodeAsPlayingNode(UJointNodeBase* SubNode)
{
	SubNode->OnJointNodeMarkedAsPendingDelegate.AddDynamic(this, &UDF_Sequence::OnSubNodePending);

	GetHostingJointInstance()->RequestNodeBeginPlay(SubNode);
}

void UDF_Sequence::PlayNextSubNode()
{
	if (!GetHostingJointInstance()) return;

	CurrentIndex++;

	while (SubNodes.IsValidIndex(CurrentIndex))
	{
		UJointNodeBase* SubNode = SubNodes[CurrentIndex];

		if (SubNode != nullptr)
		{
			SelectNodeAsPlayingNode(SubNode);

			break;
		}

		CurrentIndex++;
	}


	if (!SubNodes.IsValidIndex(CurrentIndex))
	{
		GetHostingJointInstance()->RequestNodeEndPlay(this);
	}
}


void UDF_Sequence::PostNodeBeginPlay_Implementation()
{
	//reset
	CurrentIndex = INDEX_NONE;
	
	PlayNextSubNode();
}

void UDF_Sequence::OnSubNodePending(UJointNodeBase* InNode)
{
	if (InNode == nullptr) return;

	InNode->OnJointNodeMarkedAsPendingDelegate.RemoveDynamic(this, &UDF_Sequence::OnSubNodePending);

	PlayNextSubNode();
}
