//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"

#include "DF_Sequence.generated.h"

/**
 * Sequence node is a node that you can play the node in sequence. (one by one)
 * Sub nodes attached to this node will be played after the prior sub node has been marked as pending.
 *
 */
UCLASS(Category = "Joint|Native|Core|Flow")
class JOINTNATIVE_API UDF_Sequence: public UDialogueFragment
{
	GENERATED_BODY()

public:

	UDF_Sequence();
	void SelectNodeAsPlayingNode(UDialogueNodeBase* SubNode);

	void PlayNextSubNode();

public:

	virtual void PostNodeBeginPlay_Implementation() override;

public:

	UFUNCTION()
	void OnSubNodePending(UDialogueNodeBase* InNode);

	UPROPERTY()
	int CurrentIndex = INDEX_NONE;
};
