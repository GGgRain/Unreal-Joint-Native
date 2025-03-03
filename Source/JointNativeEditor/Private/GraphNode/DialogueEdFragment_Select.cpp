//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_Select.h"

#include "JointFunctionLibrary.h"
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

	FJointEdPinDataSetting Settings;
	Settings.bAlwaysDisplayNameText = true;
	
	PinData.Add(FJointEdPinData("Out", EEdGraphPinDirection::EGPD_Output, FJointEdPinData::PinType_Joint_Normal, Settings));
}

void UDialogueEdFragment_Select::ReallocatePins()
{
	TArray<FJointEdPinData> Array;
	
	FJointEdPinDataSetting Settings;
	Settings.bAlwaysDisplayNameText = true;
	
	Array.Add(FJointEdPinData("Out", EEdGraphPinDirection::EGPD_Output, FJointEdPinData::PinType_Joint_Normal, Settings));
	
	PinData = UJointFunctionLibrary::ImplementPins(PinData, Array);
}

void UDialogueEdFragment_Select::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	UDF_Select* CastedNode = GetCastedNodeInstance<UDF_Select>();

	if (CastedNode == nullptr) return;

	//Clear the next nodes array first because will are going to reallocate them.
	CastedNode->NextNodes.Empty();

	//Iterate through the pins this graph node has.
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin == nullptr) continue;

		//Find the replicated pin from the parent-most node.
		//This is necessary because the pins on the fragment are not implemented on the graph, instead, the parent-most node of the fragment take all the pins on the fragment and replicate them, and display on the graph.
		//So to get the connections of the pins, you must get the replicated pin and get the connection from them.
		UEdGraphPin* FoundPin = FindReplicatedSubNodePin(Pin);

		if (FoundPin == nullptr) continue;

		//Iterate through the connected pins on the replicated pin.
		for (const UEdGraphPin* LinkedTo : FoundPin->LinkedTo)
		{
			if (LinkedTo == nullptr) continue;

			//Check the connected node and cast it to UDialogueEdGraphNode.
			if (LinkedTo->GetOwningNode() == nullptr) continue;
			
			UEdGraphNode* ConnectedNode = LinkedTo->GetOwningNode();

			if (!ConnectedNode) continue;
			
			UJointEdGraphNode* CastedGraphNode = Cast<UJointEdGraphNode>(ConnectedNode);

			if (!CastedGraphNode) continue;

			//Get the actual node instances from the connected node and allocate it on the Next Nodes.
			CastedGraphNode->AllocateReferringNodeInstancesOnConnection(CastedNode->NextNodes);
		}
	}
}

TSubclassOf<UJointNodeBase> UDialogueEdFragment_Select::SupportedNodeClass()
{
	return UDF_Select::StaticClass();
}

FPinConnectionResponse UDialogueEdFragment_Select::CanAttachSubNodeOnThis(const UJointEdGraphNode* InSubNode) const
{
	if (UDF_Select* Context = InSubNode->GetCastedNodeInstance<UDF_Select>())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
		                              LOCTEXT("AllowedAttachmentMessage",
		                                      "Context node can not have another context node as child."));
	}

	return Super::CanAttachSubNodeOnThis(InSubNode);
}

#undef LOCTEXT_NAMESPACE
