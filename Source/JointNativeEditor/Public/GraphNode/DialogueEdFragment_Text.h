//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/SubNode/DialogueEdGraphNode_Fragment.h"
#include "DialogueEdFragment_Text.generated.h"

class SContextTextEditor;
/**
 * 
 */
UCLASS()
class JOINTNATIVEEDITOR_API UDialogueEdFragment_Text : public UDialogueEdGraphNode_Fragment
{
	GENERATED_BODY()

public:

	UDialogueEdFragment_Text();

public:

	virtual TSubclassOf<UDialogueNodeBase> SupportedNodeClass() override;
	
	virtual void ModifyGraphNodeSlate() override;
	
	void UpdateSlate();

public:

	void OnTextChange(const FText& Text);
	void OnTextCommitted(const FText& Text, ETextCommit::Type Arg);

public:

	TSharedPtr<SVerticalBox> ContextTextEditorContainer;

	TSharedPtr<SContextTextEditor> ContextTextEditor;

public:

	UPROPERTY(Transient)
	bool bHasTransaction = false;

public:

	virtual void OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent, const FString& PropertyName) override;
	
};
