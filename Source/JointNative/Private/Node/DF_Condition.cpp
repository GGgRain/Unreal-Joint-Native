//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Condition.h"

#include "JointActor.h"

UDF_Condition::UDF_Condition()
{
	//Condition node is a decorator node.
	//NodeTags.AddTag(SDS_NodeTag_Decorator);
	
	//Condition node can be attached anywhere.
#if WITH_EDITORONLY_DATA
	bAllowDisplayClassFriendlyNameText = true;
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Stow;
	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.078125, 0.001330,0.013824, 0.700000);
	
#endif
}

void UDF_Condition::SelectNodeAsPlayingNode(UJointNodeBase* SubNode)
{
	SubNode->OnJointNodeMarkedAsPendingDelegate.AddDynamic(this, &UDF_Condition::OnSubNodePending);

	GetHostingJointInstance()->RequestNodeBeginPlay(SubNode);
}

void UDF_Condition::PlayNextSubNode()
{
	//Cancel the iteration when the condition value was false. 
	if(bConditionResult == false)
	{
		GetHostingJointInstance()->RequestNodeEndPlay(this);
		
		return;	
	}
	
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


void UDF_Condition::PostNodeBeginPlay_Implementation()
{
	PlayNextSubNode();
}

void UDF_Condition::OnSubNodePending(UJointNodeBase* InNode)
{
	if (InNode == nullptr) return;

	InNode->OnJointNodeMarkedAsPendingDelegate.RemoveDynamic(this, &UDF_Condition::OnSubNodePending);

	PlayNextSubNode();
}

