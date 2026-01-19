// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/DF_Break.h"

#include "JointActor.h"
#include "JointManager.h"
#include "JointVersionComparison.h"
#include "Node/Derived/JN_Foundation.h"

#define LOCTEXT_NAMESPACE "UDF_Break"

UDF_Break::UDF_Break()
{
#if WITH_EDITORONLY_DATA

#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(29.f / 255.f, 44.f / 255.f, 46.f / 255.f, 0.400000);
	NodeIconicColor = FLinearColor(29.f / 255.f, 44.f / 255.f, 46.f / 255.f, 0.400000);
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Stow;
	
#else

	EdNodeSetting.bUseSpecifiedGraphNodeBodyColor = true;
	EdNodeSetting.NodeBodyColor = FLinearColor(29.f / 255.f, 44.f / 255.f, 46.f / 255.f, 0.400000);
	EdNodeSetting.NodeIconicColor = FLinearColor(29.f / 255.f, 44.f / 255.f, 46.f / 255.f, 0.400000);
	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Stow;
	
#endif
	
#endif
}

void UDF_Break::Break()
{
	// If the node has ended play, do nothing - we don't allow this action.
	if (IsNodeEndedPlay()) return;
	
	bIsBroken = true;
	
	// Also mark the parentmost node as pending, so that the Joint instance will re-evaluate the flow from there.
	if (AJointActor* HostingInstance = GetHostingJointInstance())
	{
		if (UJointNodeBase* ParentmostNode = GetParentmostNode())
		{
			ParentmostNode->MarkNodePendingByForce();
			MarkNodePendingByForce();
		}
	}
}

bool UDF_Break::CheckCanMarkNodeAsPending_Implementation()
{
	// Always allow marking as pending since this node is design to never affect the flow by the playback of itself.
	return true;
}

void UDF_Break::PreNodeBeginPlay_Implementation()
{
	bIsBroken = false;
	
	Super::PreNodeBeginPlay_Implementation();
}

void UDF_Break::PostNodeBeginPlay_Implementation()
{
	Super::PostNodeBeginPlay_Implementation();
}

const FJointEdPinConnectionResponse UDF_Break::CanAttachThisAtParentNode_Implementation(const UObject* InParentNode) const
{
	//Do whatever you want if you need. 
	//We recommend you to wrap all stuffs in this function with if WITH_EDITOR macro to prevent all possible exploit on the runtime scenarios.
#if WITH_EDITOR

	//Check if the node instance is valid.
	if (InParentNode == nullptr) return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW, LOCTEXT("DisallowedAttachmentMessage", "Unknown reason"));

	//if the node instance is the same as this node, disallow the connection.
	if (InParentNode == this) return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW, LOCTEXT("DisallowedAttachmentMessage_SameNode", "Can not attach a node to the same node. How are you even doing this?"));

	// Disallow if the parent node is a Joint manager.
	if (InParentNode->IsA<UJointManager>())
	{
		return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW, LOCTEXT("DisallowedAttachmentMessage_ManagerParent", "Break node can not be attached as a manager fragment."));
	}else if (const UJointNodeBase* CastedParentNode = Cast<UJointNodeBase>(InParentNode))
	{
		// Disallow if the parent node is a manager fragment.
		if (const UJointManager* JM = CastedParentNode->GetJointManager())
		{
			if (JM->ManagerFragments.Contains(CastedParentNode))
			{
				return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW, LOCTEXT("DisallowedAttachmentMessage_ManagerFragmentParent", "Break node can not be attached as a sub node of a manager fragment."));
			}
		}
	}
	
	//Allow the connection.
	if(GEngine->IsEditor()) return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_MAKE, LOCTEXT("AllowedAttachmentMessage", "Allow Attaching"));

#endif
	
	//Runtime Fallback
	return FJointEdPinConnectionResponse(EJointEdCanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW, INVTEXT("CANNOT CHANGE ATTACHMENT ON RUNTIME"));
}

TArray<UJointNodeBase*> UDF_Break::SelectNextNodes_Implementation(AJointActor* InHostingDialogueInstance)
{
	if ( bIsBroken ) return BreakTo;
	
	return TArray<UJointNodeBase*>();
	
}

bool UDF_Break::IsSupportedForNetworking() const
{
	return false;
}

#undef LOCTEXT_NAMESPACE
