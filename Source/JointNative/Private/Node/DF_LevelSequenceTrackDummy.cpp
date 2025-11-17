//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "Node/DF_LevelSequenceTrackDummy.h"
#include "JointActor.h"

#include "JointVersionComparison.h"

#include "Materials/MaterialInstanceConstant.h"
#include "UObject/ConstructorHelpers.h"

UDF_LevelSequenceTrackDummy::UDF_LevelSequenceTrackDummy()
{

#if WITH_EDITORONLY_DATA
	
#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;
	
#elif JOINT_VERSION_OLDER_THAN(2, 11, 0)

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> NodeBodyBrush(
	TEXT(
		"MaterialInstanceConstant'/JointNative/Editor/MI_MovieTrackBody.MI_MovieTrackBody'"));
	if (NodeBodyBrush.Succeeded())
	{
		EdNodeSetting.bUseCustomOuterNodeBodyImageBrush = true;
		EdNodeSetting.OuterNodeBodyImageBrush.SetResourceObject(NodeBodyBrush.Object);
		EdNodeSetting.OuterNodeBodyImageBrush.ImageSize = FVector2D(	220.0, 196);
		EdNodeSetting.OuterNodeBodyImageBrush.DrawAs = ESlateBrushDrawType::Image;
		EdNodeSetting.OuterNodeBodyImageBrush.Margin = FMargin(0);
	}

	EdNodeSetting.bUseCustomInnerNodeBodyImageBrush = true;
	EdNodeSetting.InnerNodeBodyImageBrush.DrawAs = ESlateBrushDrawType::NoDrawType; // NoDrawType to hide the outline.
	EdNodeSetting.InnerNodeBodyImageBrush.Margin = FMargin(0.5);

	EdNodeSetting.bUseCustomNodeShadowImageBrush = true;
	EdNodeSetting.NodeShadowImageBrush.DrawAs = ESlateBrushDrawType::NoDrawType; // NoDrawType to hide the outline.

	EdNodeSetting.bUseSpecifiedGraphNodeBodyColor = true;
	EdNodeSetting.bUseIconicColorForNodeBodyOnStow = false;
	EdNodeSetting.NodeBodyColor = FLinearColor(0.001, 0.001, 0.001, 0.2);
	EdNodeSetting.NodeIconicColor = FColor(29, 130, 126, 125);
	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Maximum;

#else

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> NodeBodyBrush(
	TEXT(
		"MaterialInstanceConstant'/JointNative/Editor/MI_LevelSequencerDummy.MI_LevelSequencerDummy'"));
	if (NodeBodyBrush.Succeeded())
	{
		EdNodeSetting.bUseCustomOuterNodeBodyImageBrush = true;
		EdNodeSetting.OuterNodeBodyImageBrush.SetResourceObject(NodeBodyBrush.Object);
		EdNodeSetting.OuterNodeBodyImageBrush.ImageSize = FVector2D(	220.0, 196);
		EdNodeSetting.OuterNodeBodyImageBrush.DrawAs = ESlateBrushDrawType::Image;
		EdNodeSetting.OuterNodeBodyImageBrush.Margin = FMargin(0);
	}
	

	EdNodeSetting.bUseCustomContentNodePadding = true;
	EdNodeSetting.ContentNodePadding = FMargin(12);
	
	EdNodeSetting.bUseCustomInnerNodeBodyImageBrush = true;
	EdNodeSetting.InnerNodeBodyImageBrush.DrawAs = ESlateBrushDrawType::NoDrawType; // NoDrawType to hide the outline.

	EdNodeSetting.bUseCustomNodeShadowImageBrush = true;
	EdNodeSetting.NodeShadowImageBrush.DrawAs = ESlateBrushDrawType::NoDrawType; // NoDrawType to hide the outline.

	EdNodeSetting.bUseSpecifiedGraphNodeBodyColor = true;
	EdNodeSetting.bUseIconicColorForNodeBodyOnStow = false;
	EdNodeSetting.NodeBodyColor = FLinearColor(0.001, 0.001, 0.001, 0.2);
	EdNodeSetting.NodeIconicColor = FColor(29, 130, 126, 125);
	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Maximum;
	
#endif
	
#endif
	
}

void UDF_LevelSequenceTrackDummy::PostNodeBeginPlay_Implementation()
{
	MarkNodePendingByForce();
}

bool UDF_LevelSequenceTrackDummy::CheckCanMarkNodeAsPending_Implementation()
{
	return true;
}
