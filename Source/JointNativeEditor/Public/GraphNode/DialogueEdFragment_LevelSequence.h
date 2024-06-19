//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_LevelSequence.generated.h"

/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_LevelSequence : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_LevelSequence();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;

public:
	
	virtual FLinearColor GetNodeTitleColor() const override;
	
	void OnAssetSelectedFromPicker(const FAssetData& AssetData);
	
	virtual void ModifyGraphNodeSlate() override;

	virtual void OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName) override;
	
	void UpdateThumbnail();

public:

	TSharedPtr<SBox> AssetBox;

	TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;

	/**
	 * The Size of the thumbnail.
	 */
	UPROPERTY(EditAnywhere, Category="Visual")
	FIntPoint ThumbnailSize = FIntPoint(64,64);
	
};
