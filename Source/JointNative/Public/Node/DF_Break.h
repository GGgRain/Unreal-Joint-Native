// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"
#include "DF_Break.generated.h"


/**
 * A Joint fragment that breaks the playback of the currently playing base node and make it move to the next node immediately.
 * Break action can be triggered by calling the Break() function.
 * 
 * If you set bUseBreakTo to true, This node will provide BreakTo nodes as the next nodes when broken. It can be used to create branching paths in the Joint flow.
 * Otherwise, it will not provide any next nodes, which means this break node only breaks the current playback without affecting the next nodes.
 * (TIP: Try attaching it on the top of list so that it will be prioritized when breaking.)
 * 
 * * This node should not be a manager fragment.
 */
UCLASS(Category = "Joint Native|Flow")
class JOINTNATIVE_API UDF_Break : public UJointFragment
{
	GENERATED_BODY()
	
public:
	
	UDF_Break();

public:
	
	/**
	 * Nodes that will be played when this node is broken to.
	 * Only used when bUseBreakTo is true.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Nodes")
	TArray<TObjectPtr<UJointNodeBase>> BreakTo;

	/**
	 * If true, this node will provide BreakTo nodes as the next nodes when broken.
	 * Otherwise, it will not provide any next nodes, which means this break node only breaks the current playback without affecting the next nodes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	bool bUseBreakTo = false;
	
public:
	
	/**
	 * Execute the break action.
	 */
	UFUNCTION(BlueprintCallable, Category = "Joint Native|Node|Break")
	void Break();
	
private:
	
	// Whether this node is already broken.
 	UPROPERTY(Transient)
	bool bIsBroken = false;

public:
	
	virtual bool CheckCanMarkNodeAsPending_Implementation() override;
	virtual void PreNodeBeginPlay_Implementation() override;
	virtual void PostNodeBeginPlay_Implementation() override;
	virtual const FJointEdPinConnectionResponse CanAttachThisAtParentNode_Implementation(const UObject* InParentNode) const override;
	
public:
	
	virtual TArray<UJointNodeBase*> SelectNextNodes_Implementation(AJointActor* InHostingJointInstance) override;
	
public:
	
	virtual bool IsSupportedForNetworking() const override;
	
};
