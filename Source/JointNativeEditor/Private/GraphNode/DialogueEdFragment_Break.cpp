//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "GraphNode/DialogueEdFragment_Break.h"

#include "JointFunctionLibrary.h"
#include "Node/DF_Break.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Break"

UDialogueEdFragment_Break::UDialogueEdFragment_Break()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

TSubclassOf<UJointNodeBase> UDialogueEdFragment_Break::SupportedNodeClass()
{
	return UDF_Break::StaticClass();
}

void UDialogueEdFragment_Break::AllocateDefaultPins()
{
	UDF_Break* CastedNode = GetCastedNodeInstance<UDF_Break>();
	if (!CastedNode) return;
	
	PinData.Empty();
	
	if ( CastedNode->bUseBreakTo)
	{
		FJointEdPinDataSetting InputSetting;
		InputSetting.bAlwaysDisplayNameText = true;
	
		PinData.Add(
			FJointEdPinData(
				"On Break",
				EEdGraphPinDirection::EGPD_Output,
				InputSetting
			)
		);	
	}
}

void UDialogueEdFragment_Break::ReallocatePins()
{
	UDF_Break* CastedNode = GetCastedNodeInstance<UDF_Break>();
	if (!CastedNode) return;
	
	if ( CastedNode->bUseBreakTo)
	{
		TArray<FJointEdPinData> NewPinData;
		FJointEdPinDataSetting InputSetting;
		InputSetting.bAlwaysDisplayNameText = true;
	
		NewPinData.Add(
			FJointEdPinData(
				"On Break",
				EEdGraphPinDirection::EGPD_Output,
				InputSetting
			)
		);
		
		PinData = UJointFunctionLibrary::ImplementPins(PinData, NewPinData);
	}else
	{
		PinData.Empty();
	}
}

void UDialogueEdFragment_Break::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	UDF_Break* CastedNode = GetCastedNodeInstance<UDF_Break>();

	if (CastedNode == nullptr) return;

	CastedNode->BreakTo.Empty();

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin == nullptr) continue;
		
		//Find the replicated pin from the parent-most node.
		UEdGraphPin* FoundPin = FindReplicatedSubNodePin(Pin);

		if(FoundPin == nullptr) continue;

		if (FoundPin->PinName == "On Break")
		{
			for (UEdGraphPin* LinkedTo : FoundPin->LinkedTo)
			{
				if (UJointEdGraphNode* CastedGraphNode = CastPinOwnerToJointEdGraphNode(LinkedTo))
				{
					CastedGraphNode->AllocateReferringNodeInstancesOnConnection(CastedNode->BreakTo, LinkedTo);
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
