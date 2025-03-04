//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_Select.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDFSelectSelectionChanged, const UDF_Select*, SelectNode, const bool, NewSelection);

/**
 * An implementation of user-selectable branching option for the dialogue.
 * 
 * One select node means one option on the branching.
 * When bIsSelected is true, it will return the following next nodes for this node on the SelectNextNodes().
 * 
 * This node itself doesn't have any actions by itself. (It only implement buttons) You have to check out how the other nodes related to the select node use this node to see how they actually halt the dialogue playback and implement the selection actions. (especially DF_ServerClient_Vote)
 * 
 * You can attach some sub nodes for the select nodes and parse it to display some additional data for the widgets or etc. See how the sample widget for the Joint utilize the DF_Text on the select node like.
 * This node will be depreciated eventually and will be replaced with BP version, but not today.
 */

UCLASS(Category = "Joint Native|C++|Flow")
class JOINTNATIVE_API UDF_Select: public UJointFragment
{
	GENERATED_BODY()

public:
	
	UDF_Select();

public:

	virtual void PostNodeBeginPlay_Implementation() override;
	
	virtual TArray<UJointNodeBase*> SelectNextNodes_Implementation(AJointActor* InHostingDialogueInstance) override;

public:

	UFUNCTION(BlueprintPure, Category="Select")
	bool GetSelected() const;

	UFUNCTION(BlueprintCallable, Category="Select")
	void SetSelected(const bool bNewSelected);

public:
	
	UPROPERTY(AdvancedDisplay, VisibleAnywhere, BlueprintReadOnly, Category = "Select")
	TArray<UJointNodeBase*> NextNodes;

private:

	/**
	 * Whether this node is selected by the system.
	 * Change this value to true to let it return the nodes connected to it as the next nodes to play.
	 */
	UPROPERTY(EditAnywhere, Category="Select")
	bool bIsSelected = false;

public:
	
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category="Select")
	FDFSelectSelectionChanged OnSelectionChanged;
	
};
