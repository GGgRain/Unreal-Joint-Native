//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_TextStyle.h"

#include "Editor/Slate/GraphNode/SDialogueGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_TextStyle.h"

#include "VoltAnimationManager.h"
#include "Animation/Volt_ASA_Emerge.h"
#include "Module/Volt_ASM_InterpRenderOpacity.h"
#include "Module/Volt_ASM_InterpWidgetTransform.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_TextStyle"

UDialogueEdFragment_TextStyle::UDialogueEdFragment_TextStyle()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

FLinearColor UDialogueEdFragment_TextStyle::GetNodeTitleColor() const
{
	return FLinearColor(0.7, 0.1, 0.2);
}

bool UDialogueEdFragment_TextStyle::CanHaveSubNode() const
{
	return false;
}

FLinearColor UDialogueEdFragment_TextStyle::GetNodeBodyTintColor() const
{
	return FJointEditorStyle::Color_Normal;
}

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_TextStyle::SupportedNodeClass()
{
	return UDF_TextStyle::StaticClass();
}


void UDialogueEdFragment_TextStyle::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	StyleBox = SNew(SVerticalBox);

	NodeSlate->CenterContentBox->AddSlot()
		.HAlign(HAlign_Fill)
		//.VAlign(VAlign_Fill)
		.Padding(FJointEditorStyle::Margin_Frame)
		[
			StyleBox.ToSharedRef()
		];

	UpdateSlate();
}

void UDialogueEdFragment_TextStyle::OnNodeInstancePropertyChanged(
	const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	UpdateSlate();
}

void UDialogueEdFragment_TextStyle::UpdateSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	UDF_TextStyle* CastedNodeInstance = GetCastedNodeInstance<UDF_TextStyle>();

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
						.Image(FJointEditorStyle::GetUEEditorSlateStyleSet().GetBrush("DetailsView.EditRawProperties"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[

					SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(CastedNodeInstance->TextStyleTable != nullptr
						      ? FText::FromString(CastedNodeInstance->TextStyleTable->GetName())
						      : LOCTEXT("NoInstance", "No Text Style Table"))

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

	StyleBox->ClearChildren();

	StyleBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			ConditionSlate.ToSharedRef()
		];
}

bool UDialogueEdFragment_TextStyle::CanHaveBreakpoint() const
{
	return false;
}


#undef LOCTEXT_NAMESPACE
