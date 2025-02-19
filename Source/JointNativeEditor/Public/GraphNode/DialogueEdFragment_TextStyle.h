//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/JointEdGraphNode_Fragment.h"
#include "DialogueEdFragment_TextStyle.generated.h"

class UVoltAnimationManager;
class SScrollBox;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_TextStyle : public UJointEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_TextStyle();

public:

	virtual TSubclassOf<UJointNodeBase> SupportedNodeClass() override;


public:

	virtual bool CanHaveSubNode() const override;


public:

	virtual void ModifyGraphNodeSlate() override;

	virtual void OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName) override;

	void UpdateSlate();

	virtual bool CanHaveBreakpoint() const override;
	
public:

	/**
	 * A box that holds the style representing slate.
	 */
	TSharedPtr<SVerticalBox> StyleBox;
	
};
