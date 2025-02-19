//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_Sequence.h"

#include "Editor/Slate/GraphNode/SJointGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_Sequence.h"


#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Random"

UDialogueEdFragment_Sequence::UDialogueEdFragment_Sequence()
{
	bUseFixedNodeSize = false;
}

TSubclassOf<UJointNodeBase> UDialogueEdFragment_Sequence::SupportedNodeClass()
{
	return UDF_Sequence::StaticClass();
}

void UDialogueEdFragment_Sequence::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SJointGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	if(NodeSlate && NodeSlate->NameBox)
	{
		NodeSlate->NameBox->AddSlot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(FJointEditorStyle::Margin_Border)
		[
			SNew(SBox)
			.Visibility(EVisibility::SelfHitTestInvisible)
			.WidthOverride(16)
			.HeightOverride(16)
			[
				SNew(SImage)
				.Image(FJointEditorStyle::GetUEEditorSlateStyleSet().GetBrush("TimelineEditor.Replicated"))
				.ToolTipText(LOCTEXT("AsynchoronousMessage","This node's action is asynchoronous.\nThe execution of the sub nodes of this node will not follow the flow of the dialogue."))
			]
		];
	}

}



#undef LOCTEXT_NAMESPACE
