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

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	UDF_SpeakerAndListener* CastedNodeInstance = GetCastedNodeInstance<UDF_SpeakerAndListener>();

	if (NodeSlate && NodeSlate->CenterContentBox && CastedNodeInstance)
	{
		const TAttribute<EVisibility> SpeakersBoxVisibility_Attr = TAttribute<EVisibility>::CreateLambda([CastedNodeInstance]
		{
			return CastedNodeInstance && CastedNodeInstance->Speakers.Num() > 0
				       ? EVisibility::SelfHitTestInvisible
				       : EVisibility::Collapsed;
		});

		const TAttribute<EVisibility> ChevronVisibility_Attr = TAttribute<EVisibility>::CreateLambda([CastedNodeInstance]
		{
			return (CastedNodeInstance && CastedNodeInstance->Speakers.Num() > 0) || (CastedNodeInstance && CastedNodeInstance->Listeners.Num() > 0)
				       ? EVisibility::SelfHitTestInvisible
				       : EVisibility::Collapsed;
		});

		const TAttribute<EVisibility> ListenersBoxVisibility_Attr = TAttribute<EVisibility>::CreateLambda([CastedNodeInstance]
		{
			return CastedNodeInstance && CastedNodeInstance->Listeners.Num() > 0
				       ? EVisibility::SelfHitTestInvisible
				       : EVisibility::Collapsed;
		});

		const TAttribute<EVisibility> ClearParticipantBorderVisibility_Attr = TAttribute<EVisibility>::CreateLambda(
			[CastedNodeInstance]
			{
				return CastedNodeInstance && CastedNodeInstance->Listeners.Num() + CastedNodeInstance->Speakers.Num() <= 0
					       ? EVisibility::SelfHitTestInvisible
					       : EVisibility::Collapsed;
			});


		NodeSlate->CenterContentBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.RenderTransformPivot(FVector2D(0.5))
				.BorderImage(FJointEditorStyle::Get().GetBrush("JointUI.Border.NodeShadow"))
				.BorderBackgroundColor(FJointEditorStyle::Color_Node_Shadow)
				.Padding(FJointEditorStyle::Margin_Shadow)
				.Visibility(ClearParticipantBorderVisibility_Attr)
				[
					SNew(SBorder)
					.BorderImage(FJointEditorStyle::Get().GetBrush("JointUI.Border.Round"))
					.BorderBackgroundColor(FJointEditorStyle::Color_Normal * 0.5)
					.Padding(FJointEditorStyle::Margin_Frame)
					.Visibility(EVisibility::HitTestInvisible)
					[
						SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(LOCTEXT("ClearParticpant", "No Participants (Clear)"))
						.TextStyle(FJointEditorStyle::Get(), "JointUI.TextBlock.Black.h5")
						.Visibility(EVisibility::HitTestInvisible)
					]
				]
			];

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
}

void UDialogueEdFragment_SpeakerAndListener::UpdateSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	if (NodeSlate && NodeSlate->CenterContentBox)
	{
		SpeakersBox->ClearChildren();
		ListenersBox->ClearChildren();

		UDF_SpeakerAndListener* SpeakerAndListener = GetCastedNodeInstance<UDF_SpeakerAndListener>();

		if (SpeakerAndListener == nullptr) return;


		for (int i = 0; i < SpeakerAndListener->Listeners.Num(); ++i)
		{
			if (!SpeakerAndListener->Listeners.IsValidIndex(i)) continue;

			FDialogueNodePointer& Listener = SpeakerAndListener->Listeners[i];

			const TAttribute<FText> DisplayText_Attr = TAttribute<FText>::Create(
				TAttribute<FText>::FGetter::CreateLambda(
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
				.Visibility(EVisibility::SelfHitTestInvisible)
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

			const TAttribute<FText> DisplayText_Attr = TAttribute<FText>::Create(
				TAttribute<FText>::FGetter::CreateLambda(
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
				.Visibility(EVisibility::SelfHitTestInvisible)
				.GraphContextObject(this)
				.DisplayName(DisplayText_Attr)
				.PointerToStructure(&Speaker)
				.bShouldShowDisplayName(true)
				.bShouldShowNodeName(true)
			];
		}
	}
}


void UDialogueEdFragment_SpeakerAndListener::OnNodeInstancePropertyChanged(
	const FPropertyChangedEvent& PropertyChangedEvent,
	const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	UpdateSlate();
}

#undef LOCTEXT_NAMESPACE
