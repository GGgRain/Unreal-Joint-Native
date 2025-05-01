//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Sequence.h"
#include "JointActor.h"

#include "JointVersionComparison.h"

UDF_Sequence::UDF_Sequence()
{

#if WITH_EDITORONLY_DATA
	
#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;
	
#else

	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;

#endif
	
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
