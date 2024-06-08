//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_Select.h"

#include "Node/DF_Select.h"


#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Select"

UDialogueEdFragment_Select::UDialogueEdFragment_Select()
{
	NodeWidth = 0;
	NodeHeight = 0;

	bUseFixedNodeSize = false;
}

void UDialogueEdFragment_Select::AllocateDefaultPins()
{
	PinData.Empty();

	PinData.Add(FDialogueEdPinData("Out", EEdGraphPinDirection::EGPD_Output));
}

void UDialogueEdFragment_Select::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	UDF_Select* CastedNode = GetCastedNodeInstance<UDF_Select>();

	if (CastedNode == nullptr) return;

	CastedNode->NextNodes.Empty();

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin == nullptr) continue;

		//Find the replicated pin from the parent-most node.
		UEdGraphPin* FoundPin = FindReplicatedSubNodePin(Pin);

		if (FoundPin == nullptr) continue;

		for (const UEdGraphPin* LinkedTo : FoundPin->LinkedTo)
		{
			if (LinkedTo == nullptr) continue;

			if (LinkedTo->GetOwningNode() == nullptr) continue;

			UEdGraphNode* ConnectedNode = LinkedTo->GetOwningNode();

			if (!ConnectedNode) continue;

			UDialogueEdGraphNode* CastedGraphNode = Cast<UDialogueEdGraphNode>(ConnectedNode);

			if (!CastedGraphNode) continue;

			CastedGraphNode->AllocateReferringNodeInstancesOnConnection(CastedNode->NextNodes);
		}
	}
}

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_Select::SupportedNodeClass()
{
	return UDF_Select::StaticClass();
}

FPinConnectionResponse UDialogueEdFragment_Select::CanAttachSubNodeOnThis(const UDialogueEdGraphNode* InSubNode) const
{
	if (UDF_Select* Context = InSubNode->GetCastedNodeInstance<UDF_Select>())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
		                              LOCTEXT("AllowedAttachmentMessage",
		                                      "Context node can not have another context node as child."));
	}

	return Super::CanAttachSubNodeOnThis(InSubNode);
}

FLinearColor UDialogueEdFragment_Select::GetNodeTitleColor() const
{
	return FLinearColor(0.4f, 0.2f, 0.5f);
}

#undef LOCTEXT_NAMESPACE
