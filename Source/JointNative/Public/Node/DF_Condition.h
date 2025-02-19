//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_Condition.generated.h"

/**
 * A fragment for the conditional check on the dialogue manager.
 * 
 * It will play through the sub nodes one by one asynchronously just like the sequence node does, but it will break the iteration when any sub node changes the bConditionResult value to false.
 * 
 * Implement some sub nodes and change bConditionResult value from the sub node side to implement the condition action.
 */
UCLASS(Category = "Joint Native|C++|Condition", Hidden, meta=(DeprecatedNode, DeprecationMessage="Deprecated on Joint Native 1.9.0. Use Condition AND instead"))
class JOINTNATIVE_API UDF_Condition : public UJointFragment
{
	GENERATED_BODY()

public:
	UDF_Condition();

public:
	/**
	 * Whether this condition node has succeeded to make through the test.
	 * Access this value and change it to control the result of the condition check.
	 * If this value become false, then it will cancel the iteration.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Condition")
	bool bConditionResult = true;

public:
	virtual void PostNodeBeginPlay_Implementation() override;

	UFUNCTION()
	void OnSubNodePending(UJointNodeBase* InNode);

public:
	void SelectNodeAsPlayingNode(UJointNodeBase* SubNode);

	void PlayNextSubNode();

	UPROPERTY()
	int CurrentIndex = INDEX_NONE;
};
