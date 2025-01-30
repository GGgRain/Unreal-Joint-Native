//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/DialogueFragment.h"

#include "SharedType/DialogueSharedTypes.h"
#include "DF_Branch.generated.h"

/**
 * Branch node is a most fundamental node for the flow control of the graph.
 * You can control the flow of the dialogue by attaching a condition node on this node.
 * 
 * If the attached condition node passes the condition check, branch node will play the nodes at the true pin.
 * Otherwise, it will play the nodes at the false pin.
 *
 * You can disable the false pin with bUseFalse variable.
 * When the false pin is disabled, dialogue instance will continue to the next branch node if available.
 * So you can create simple if-else branching with it.
 *
 * It will not return any of the nodes if it was not played.
 * Joint Native 1.6.0 : Not recommended to use anymore. Use DF_Branching instead.
 */
UCLASS(Category = "Joint|Native|Core|Flow", meta=(DeprecationMessage="Deprecated on Joint Native 1.6.0 : Not recommended to use anymore. Use DF_Branching instead."))
class JOINTNATIVE_API UDF_Branch: public UDialogueFragment
{
	GENERATED_BODY()
	
public:

	UDF_Branch();

	//Nodes that will be played when this node's condition check passes
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Nodes")
	TArray<UDialogueNodeBase*> TrueNode;


	//Nodes that will be played when this node's condition check fails
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Nodes")
	TArray<UDialogueNodeBase*> FalseNode;


public:

	/**
	 * Whether to use false pin.
	 * When the false pin is disabled, dialogue instance will continue to the next branch node if available.
	 * So you can create simple if-else branching with it.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Branch Control")
	bool bUseFalse = true;
	
public:
	
	virtual TArray<UDialogueNodeBase*> SelectNextNodes_Implementation(const TSoftObjectPtr<ADialogueActor>& InHostingDialogueInstance) override;
};
