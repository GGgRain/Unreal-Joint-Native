//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DialogueEdFragment_Branch.h"

#include "DialogueManager.h"
#include "Misc/UObjectToken.h"
#include "Node/DF_Branch.h"
#include "Node/DF_Condition.h"

#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Branch"

UDialogueEdFragment_Branch::UDialogueEdFragment_Branch()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_Branch::SupportedNodeClass()
{
	return UDF_Branch::StaticClass();
}

void UDialogueEdFragment_Branch::OnCompileNode()
{

	Super::OnCompileNode();
	
	if (GetCastedNodeInstance())
	{
		if (!GetCastedNodeInstance()->FindFragmentByClass(UDF_Condition::StaticClass()))
		{
			TSharedRef<FTokenizedMessage> TokenizedMessage = FTokenizedMessage::Create(EMessageSeverity::Info);
			TokenizedMessage->AddToken(FAssetNameToken::Create(GetDialogueManager() ? GetDialogueManager()->GetName() : "NONE"));
			TokenizedMessage->AddToken(FTextToken::Create(FText::FromString(":")));
			TokenizedMessage->AddToken(FUObjectToken::Create(this));
			TokenizedMessage->AddToken(FTextToken::Create(LOCTEXT("Compile_NoCondition","No condition node has been attached. Branch node must have one condition fragment as sub node to work properly. It will always return the nodes at the true pins if it has been played.")) );
			TokenizedMessage.Get().SetMessageLink(FUObjectToken::Create(this));
			
			CompileMessages.Add(TokenizedMessage);
			
		}
	}
}

void UDialogueEdFragment_Branch::AllocateDefaultPins()
{
	PinData.Empty();

	PinData.Add(FDialogueEdPinData("True", EEdGraphPinDirection::EGPD_Output));
	PinData.Add(FDialogueEdPinData("False", EEdGraphPinDirection::EGPD_Output));
}

void UDialogueEdFragment_Branch::ReallocatePins()
{
	UDF_Branch* CastedNodeInstance = GetCastedNodeInstance<UDF_Branch>();

	if (CastedNodeInstance == nullptr) return;

	//Collect all the False pins by whether they are actually implemented or not.
	TArray<FDialogueEdPinData> NotImplementedFalsePinData;
	TArray<FDialogueEdPinData> FalsePinData;


	for (const FDialogueEdPinData& Data : PinData)
	{
		if (Data.PinName == "False")
		{
			if (Data.ImplementedPinId == FGuid())
			{
				NotImplementedFalsePinData.Add(Data);
			}
			else
			{
				FalsePinData.Add(Data);
			}
		}
	}

	//attach the NotImplementedFalsePinData at the tail so we can pop out those first.
	FalsePinData.Append(NotImplementedFalsePinData);


	if (!CastedNodeInstance->bUseFalse)
	{
		//Remove the false pin.
		for (FDialogueEdPinData DialogueEdPinData : FalsePinData)
		{
			PinData.Remove(DialogueEdPinData);
		}
	}
	else
	{
		//Restore the false pin.

		//Pop out if we have too many of them. 
		while (FalsePinData.Num() > 1)
		{
			PinData.Remove(FalsePinData.Last());
			FalsePinData.Pop();
		}

		if (FalsePinData.IsEmpty())
		{
			PinData.Add(FDialogueEdPinData("False", EEdGraphPinDirection::EGPD_Output));
		}
	}
}

void UDialogueEdFragment_Branch::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	UDF_Branch* CastedNode = GetCastedNodeInstance<UDF_Branch>();

	if (CastedNode == nullptr) return;

	CastedNode->TrueNode.Empty();
	CastedNode->FalseNode.Empty();

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin == nullptr) continue;
		
		//Find the replicated pin from the parent-most node.
		UEdGraphPin* FoundPin = FindReplicatedSubNodePin(Pin);

		if(FoundPin == nullptr) continue;

		if (FoundPin->PinName == "True")
		{
			for (const UEdGraphPin* LinkedTo : FoundPin->LinkedTo)
			{
				if (LinkedTo == nullptr) continue;

				if (LinkedTo->GetOwningNode() == nullptr) continue;

				UEdGraphNode* ConnectedNode = LinkedTo->GetOwningNode();

				if (!ConnectedNode) continue;

				UDialogueEdGraphNode* CastedGraphNode = Cast<UDialogueEdGraphNode>(ConnectedNode);

				if (!CastedGraphNode) continue;

				CastedGraphNode->AllocateReferringNodeInstancesOnConnection(CastedNode->TrueNode);
			}
		}
		else if (FoundPin->PinName == "False")
		{
			for (const UEdGraphPin* LinkedTo : FoundPin->LinkedTo)
			{
				if (LinkedTo == nullptr) continue;

				if (LinkedTo->GetOwningNode() == nullptr) continue;

				UEdGraphNode* ConnectedNode = LinkedTo->GetOwningNode();

				if (!ConnectedNode) continue;

				UDialogueEdGraphNode* CastedGraphNode = Cast<UDialogueEdGraphNode>(ConnectedNode);

				if (!CastedGraphNode) continue;

				CastedGraphNode->AllocateReferringNodeInstancesOnConnection(CastedNode->FalseNode);
			}
		}
	}
}

FPinConnectionResponse UDialogueEdFragment_Branch::CanAttachSubNodeOnThis(const UDialogueEdGraphNode* InSubNode) const
{
	UDF_Branch* CastedNodeInstance = GetCastedNodeInstance<UDF_Branch>();

	if (CastedNodeInstance == nullptr)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
		                              LOCTEXT("DisallowedAttachmentMessageUnknown",
		                                      "Unknown reason"));


	if (InSubNode->GetCastedNodeInstance<UDF_Condition>())
	{
		return Super::CanAttachSubNodeOnThis(InSubNode);
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
	                              LOCTEXT("DisallowedAttachmentMessage",
	                                      "Branch Node can have only the condition node as children."));
}


#undef LOCTEXT_NAMESPACE
