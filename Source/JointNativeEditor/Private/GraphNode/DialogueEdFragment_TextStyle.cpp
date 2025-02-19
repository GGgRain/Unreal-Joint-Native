//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_TextStyle.h"

#include "Editor/Slate/GraphNode/SJointGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_TextStyle.h"

#include "VoltDecl.h"
#include "Module/Volt_ASM_InterpRenderOpacity.h"
#include "Module/Volt_ASM_InterpWidgetTransform.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_TextStyle"

UDialogueEdFragment_TextStyle::UDialogueEdFragment_TextStyle()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

bool UDialogueEdFragment_TextStyle::CanHaveSubNode() const
{
	return false;
}

TSubclassOf<UJointNodeBase> UDialogueEdFragment_TextStyle::SupportedNodeClass()
{
	return UDF_TextStyle::StaticClass();
}


void UDialogueEdFragment_TextStyle::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SJointGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	if(NodeSlate && NodeSlate->CenterContentBox)
	{
		StyleBox = SNew(SVerticalBox)
			.Visibility(EVisibility::SelfHitTestInvisible);

		NodeSlate->CenterContentBox->AddSlot()
			.HAlign(HAlign_Fill)
			.Padding(FJointEditorStyle::Margin_Frame)
			[
				StyleBox.ToSharedRef()
			];

		UpdateSlate();
	}
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

	const TSharedPtr<SJointGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	if(NodeSlate && NodeSlate->CenterContentBox)
	{
		
		UDF_TextStyle* CastedNodeInstance = GetCastedNodeInstance<UDF_TextStyle>();

		if (CastedNodeInstance == nullptr) return;

		TSharedPtr<SWidget> ConditionSlate =
			SNew(SBorder)
			.Visibility(EVisibility::HitTestInvisible)
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


		const UVoltAnimation* Anim = VOLT_MAKE_ANIMATION(UVoltAnimation)
		(
			VOLT_MAKE_MODULE(UVolt_ASM_InterpRenderOpacity)
			.TargetOpacity(1)
			.RateBasedInterpSpeed(10),
			VOLT_MAKE_MODULE(UVolt_ASM_InterpWidgetTransform)
			.StartWidgetTransform(FWidgetTransform(
			FVector2D::ZeroVector,
			FVector2D(0.9, 0.9),
			FVector2D::ZeroVector,
			0))
			.RateBasedInterpSpeed(10)
		);
	
		VOLT_PLAY_ANIM(ConditionSlate, Anim);
	
		StyleBox->ClearChildren();

		StyleBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				ConditionSlate.ToSharedRef()
			];
	}
}

bool UDialogueEdFragment_TextStyle::CanHaveBreakpoint() const
{
	return false;
}


#undef LOCTEXT_NAMESPACE
