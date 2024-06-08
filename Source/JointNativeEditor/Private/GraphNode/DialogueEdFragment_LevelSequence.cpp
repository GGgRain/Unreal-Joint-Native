//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DialogueEdFragment_LevelSequence.h"

#include "LevelSequence.h"
#include "Editor/Slate/GraphNode/SDialogueGraphNodeBase.h"
#include "Editor/Style/JointEditorStyle.h"
#include "Node/DF_LevelSequence.h"
#include "PropertyCustomizationHelpers.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_LevelSequence"

UDialogueEdFragment_LevelSequence::UDialogueEdFragment_LevelSequence()
{
	NodeWidth = 200;
	NodeHeight = 200;
}

FLinearColor UDialogueEdFragment_LevelSequence::GetNodeTitleColor() const
{
	return FLinearColor(0.3, 0.05, 0.1);
}

void UDialogueEdFragment_LevelSequence::OnAssetSelectedFromPicker(const FAssetData& AssetData)
{
	if (!GetCastedNodeInstance<UDF_LevelSequence>()) return;

	if (AssetData.GetAsset() && Cast<ULevelSequence>(AssetData.GetAsset()))
	{
		GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay = Cast<ULevelSequence>(AssetData.GetAsset());
	}
	else
	{
		GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay = nullptr;
	}

	UpdateThumbnail();
}

void UDialogueEdFragment_LevelSequence::ModifyGraphNodeSlate()
{
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate();

	if (!GetCastedNodeInstance<UDF_LevelSequence>()) return;

	const TAttribute<FString> AssetPath_Attr = TAttribute<FString>::Create(TAttribute<FString>::FGetter::CreateLambda(
		[this]
		{
			if (GetCastedNodeInstance<UDF_LevelSequence>() && GetCastedNodeInstance<UDF_LevelSequence>()->
				SequenceToPlay)
			{
				return GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay->GetPathName();
			}

			return FString();
		}));

	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(24, true));


	NodeSlate->CenterContentBox->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(FJointEditorStyle::Margin_Border)
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FJointEditorStyle::Margin_Frame)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				[
					SNew(SBorder)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.Padding(FMargin(0, 0, 4, 4))
					.BorderImage(FAppStyle::Get().GetBrush("PropertyEditor.AssetTileItem.DropShadow"))
					[
						SNew(SOverlay)
						+ SOverlay::Slot()
						.Padding(1)
						[
							SNew(SBorder)
							.Padding(0)
							.BorderImage(FStyleDefaults::GetNoBrush())
							[
								SAssignNew(AssetBox, SBox)
								.WidthOverride(ThumbnailSize.X)
								.HeightOverride(ThumbnailSize.Y)
							]
						]
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FJointEditorStyle::Margin_Frame)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				[
					SNew(SObjectPropertyEntryBox)
					.DisplayBrowse(true)
					.EnableContentPicker(true)
					.AllowClear(true)
					.ObjectPath(AssetPath_Attr)
					.AllowedClass(ULevelSequence::StaticClass())
					.OnObjectChanged_UObject(this, &UDialogueEdFragment_LevelSequence::OnAssetSelectedFromPicker)
				]
		];

	UpdateThumbnail();
}

void UDialogueEdFragment_LevelSequence::OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent,
                                                                      const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	UpdateThumbnail();
}

void UDialogueEdFragment_LevelSequence::UpdateThumbnail()
{
	//Only update the thumbnail.

	TSharedPtr<FAssetThumbnail> AssetThumbnail = MakeShareable(
		new FAssetThumbnail(nullptr, ThumbnailSize.X, ThumbnailSize.Y, AssetThumbnailPool));

	if (GetCastedNodeInstance<UDF_LevelSequence>() && !GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay.IsNull())
	{
		if(!GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay.IsValid())
		{
			GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay.LoadSynchronous();
		}
		
		AssetThumbnail = MakeShareable(new FAssetThumbnail(
			GetCastedNodeInstance<UDF_LevelSequence>()->SequenceToPlay.Get(),
			ThumbnailSize.X,
			ThumbnailSize.Y,
			AssetThumbnailPool));
	}

	AssetBox->SetContent(AssetThumbnail->MakeThumbnailWidget());
}

TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_LevelSequence::SupportedNodeClass()
{
	return UDF_LevelSequence::StaticClass();
}

#undef LOCTEXT_NAMESPACE
