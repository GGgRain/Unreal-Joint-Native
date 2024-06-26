//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_Participant.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_Participant.h"

#include "Editor/Slate/GraphNode/SDialogueGraphNodeBase.h"
#include "Editor/Slate/GraphNode/SDialogueGraphNodeSubNodeBase.h"

//VOLT

#include "VoltAnimationManager.h"
#include "Animation/Volt_ASA_Emerge.h"
#include "Module/Volt_ASM_InterpRenderOpacity.h"
#include "Module/Volt_ASM_InterpWidgetTransform.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Participant"

UDialogueEdFragment_Participant::UDialogueEdFragment_Participant()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

FLinearColor UDialogueEdFragment_Participant::GetNodeTitleColor() const
{
	return FLinearColor(0.06f, 0.2f, 0.25f);
}

FText UDialogueEdFragment_Participant::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
	//return FText::GetEmpty();
}

FLinearColor UDialogueEdFragment_Participant::GetNodeBodyTintColor() const
{
	if (ParentNode && Cast<UDialogueEdFragment_Participant>(ParentNode)) return FJointEditorStyle::Color_Normal;

	return Super::GetNodeBodyTintColor();
}

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_Participant::SupportedNodeClass()
{
	return UDF_Participant::StaticClass();
}


void UDialogueEdFragment_Participant::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	ParticipantBox = SNew(SVerticalBox);

	NodeSlate->CenterContentBox->AddSlot()
		.HAlign(HAlign_Fill)
		//.VAlign(VAlign_Fill)
		.Padding(FJointEditorStyle::Margin_Frame)
		[
			ParticipantBox.ToSharedRef()
		];

	UpdateSlate();
}

void UDialogueEdFragment_Participant::OnNodeInstancePropertyChanged(
	const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	//Force update
	if (Cast<UDialogueEdFragment_Participant>(ParentNode)) Cast<UDialogueEdFragment_Participant>(ParentNode)->UpdateSlate();

	UpdateSlate();
}

void UDialogueEdFragment_Participant::UpdateSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeSubNodeBase> NodeSlate = StaticCastSharedPtr<SDialogueGraphNodeSubNodeBase>(
		GetGraphNodeSlate());

	UDF_Participant* CastedNodeInstance = GetCastedNodeInstance<UDF_Participant>();

	if (CastedNodeInstance == nullptr) return;

	TSharedPtr<SWidget> ConditionSlate =
		SNew(SBorder)
		.BorderImage(FJointEditorStyle::Get().GetBrush("JointUI.Border.Round"))
		.BorderBackgroundColor(GetNodeBodyTintColor())
		.Padding(FJointEditorStyle::Margin_Border)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FJointEditorStyle::Get().GetBrush("JointUI.Border.Empty"))
			.Padding(FMargin(0))
			.HAlign(HAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				//.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				.Padding(FJointEditorStyle::Margin_Frame)
				[
					SNew(SBox)
					.HeightOverride(16)
					.WidthOverride(16)
					[
						SNew(SImage)
						.Image(FJointEditorStyle::GetUEEditorSlateStyleSet().GetBrush("ShowFlagsMenu.SubMenu.Developer"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[

					SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(FText::FromString(CastedNodeInstance->ParticipantTag.ToString()))

				]
			]
		];


	UVolt_ASA_Emerge* Anim_Emerge = VOLT_GET_ANIMATION<UVolt_ASA_Emerge>(UVolt_ASA_Emerge::StaticClass());

	if (Anim_Emerge)
	{
		if (UVolt_ASM_InterpRenderOpacity* OpacityModule = Anim_Emerge->GetModuleForClass<
			UVolt_ASM_InterpRenderOpacity>())
		{
			OpacityModule->InterpSpeed = 10;
		}

		if (UVolt_ASM_InterpWidgetTransform* WidgetTransformModule = Anim_Emerge->GetModuleForClass<
			UVolt_ASM_InterpWidgetTransform>())
		{
			WidgetTransformModule->StartWidgetTransform = FWidgetTransform(
		FVector2D::ZeroVector,
		FVector2D(0.9, 0.9),
		FVector2D::ZeroVector,
		0);
			WidgetTransformModule->InterpSpeed = 10;
		}

		VOLT_PLAY_ANIM(NodeSlate->GetAnimationManager(), ConditionSlate, Anim_Emerge);
	}

	ParticipantBox->ClearChildren();

	ParticipantBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			ConditionSlate.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE
