//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DialogueEdFragment_Condition.h"

#include "Editor/Slate/GraphNode/SJointGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_Condition.h"

#include "JointVersionComparison.h"


#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Condition"

UDialogueEdFragment_Condition::UDialogueEdFragment_Condition()
{

#if JOINT_VERSION_NEWER_THAN(2,7,0)

	NodeWidth = JointGraphNodeResizableDefs::MaxFragmentSize.X;
	NodeHeight = JointGraphNodeResizableDefs::MaxFragmentSize.Y;
	
#else

	NodeWidth = 200;
	NodeHeight = 200;
	
#endif
	
}

void UDialogueEdFragment_Condition::ModifyGraphNodeSlate()
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
			.Visibility(EVisibility::HitTestInvisible)
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

TSubclassOf<UJointNodeBase> UDialogueEdFragment_Condition::SupportedNodeClass()
{
	return UDF_Condition::StaticClass();
}

#undef LOCTEXT_NAMESPACE
