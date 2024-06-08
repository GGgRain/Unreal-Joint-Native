//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DialogueEdFragment_SpeakerAndListener.h"

#include "Editor/Slate/GraphNode/DialogueGraphNodeSharedSlates.h"
#include "Editor/Slate/GraphNode/SDialogueGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_Participant.h"
#include "Node/DF_SpeakerAndListener.h"


#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_SpeakerAndListener"

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_SpeakerAndListener::SupportedNodeClass()
{
	return UDF_SpeakerAndListener::StaticClass();
}

void UDialogueEdFragment_SpeakerAndListener::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TAttribute<EVisibility> SpeakersBoxVisibility_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda([this]
		{
			if (SpeakersBox.Get()->GetChildren()->Num() > 0) return EVisibility::Visible;

			return EVisibility::Collapsed;
		}));

	const TAttribute<EVisibility> ChevronVisibility_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda([this]
		{
			if (ListenersBox.Get()->GetChildren()->Num() > 0) return EVisibility::Visible;

			return EVisibility::Collapsed;
		}));

	const TAttribute<EVisibility> ListenersBoxVisibility_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda([this]
		{
			if (ListenersBox.Get()->GetChildren()->Num() > 0) return EVisibility::Visible;

			return EVisibility::Collapsed;
		}));


	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	NodeSlate->CenterContentBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(SpeakersBox, SScrollBox)
			.Visibility(SpeakersBoxVisibility_Attr)
		];

	NodeSlate->CenterContentBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(FJointEditorStyle::GetUEEditorSlateStyleSet().GetBrush("Icons.ChevronDown"))
			.Visibility(ChevronVisibility_Attr)
		];

	NodeSlate->CenterContentBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(ListenersBox, SScrollBox)
			.Visibility(ListenersBoxVisibility_Attr)
		];

	UpdateSlate();
}

void UDialogueEdFragment_SpeakerAndListener::UpdateSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	SpeakersBox->ClearChildren();
	ListenersBox->ClearChildren();

	UDF_SpeakerAndListener* SpeakerAndListener = GetCastedNodeInstance<UDF_SpeakerAndListener>();

	if (SpeakerAndListener == nullptr) return;


	for (int i = 0; i < SpeakerAndListener->Listeners.Num(); ++i)
	{
		if (!SpeakerAndListener->Listeners.IsValidIndex(i)) continue;

		FDialogueNodePointer& Listener = SpeakerAndListener->Listeners[i];

		const TAttribute<FText> DisplayText_Attr = TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateLambda(
			[Listener]
			{
				if (Listener.Node == nullptr) return LOCTEXT("NoParticipant", "No Participant Specified");
				if (const UDF_Participant* CastedNode = Cast<UDF_Participant>(Listener.Node.Get()))
					return FText::FromString(
						CastedNode->ParticipantTag.ToString());

				return FText::GetEmpty();
			}));

		ListenersBox->AddSlot()
		[
			SNew(SDialogueNodePointerSlate)
			.GraphContextObject(this)
			.DisplayName(DisplayText_Attr)
			.PointerToStructure(&Listener)
			.bShouldShowDisplayName(true)
			.bShouldShowNodeName(true)

		];
	}

	for (int i = 0; i < SpeakerAndListener->Speakers.Num(); ++i)
	{
		if (!SpeakerAndListener->Speakers.IsValidIndex(i)) continue;

		FDialogueNodePointer& Speaker = SpeakerAndListener->Speakers[i];

		const TAttribute<FText> DisplayText_Attr = TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateLambda(
			[Speaker]
			{
				if (Speaker.Node == nullptr) return LOCTEXT("NoParticipant", "No Participant Specified");
				if (const UDF_Participant* CastedNode = Cast<UDF_Participant>(Speaker.Node.Get()))
					return FText::FromString(
						CastedNode->ParticipantTag.ToString());

				return FText::GetEmpty();
			}));

		SpeakersBox->AddSlot()
		[
			SNew(SDialogueNodePointerSlate)
			.GraphContextObject(this)
			.DisplayName(DisplayText_Attr)
			.PointerToStructure(&Speaker)
			.bShouldShowDisplayName(true)
			.bShouldShowNodeName(true)
		];
	}
}

FLinearColor UDialogueEdFragment_SpeakerAndListener::GetNodeTitleColor() const
{
	return FLinearColor(0.05f, 0.15f, 0.2f);
}


void UDialogueEdFragment_SpeakerAndListener::OnNodeInstancePropertyChanged(
	const FPropertyChangedEvent& PropertyChangedEvent,
	const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	UpdateSlate();
}

#undef LOCTEXT_NAMESPACE
