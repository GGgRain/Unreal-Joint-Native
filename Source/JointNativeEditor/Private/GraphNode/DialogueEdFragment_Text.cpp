//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DialogueEdFragment_Text.h"

#include "Editor/JointEdUtils.h"
#include "Editor/Slate/GraphNode/SDialogueGraphNodeBase.h"
#include "Editor/Slate/TextEditor/SContextTextEditor.h"
#include "Node/DF_Text.h"

#define LOCTEXT_NAMESPACE "UDialogueEdFragment_Text"


UDialogueEdFragment_Text::UDialogueEdFragment_Text()
{
	NodeWidth = 0;
	NodeHeight = 0;

	bUseFixedNodeSize = false;
}


TSubclassOf<UDialogueNodeBase> UDialogueEdFragment_Text::SupportedNodeClass()
{
	return UDF_Text::StaticClass();
}


void UDialogueEdFragment_Text::ModifyGraphNodeSlate()
{
	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	NodeSlate->CenterContentBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(ContextTextEditorContainer, SVerticalBox)
			.Visibility(EVisibility::SelfHitTestInvisible)
		];

	UpdateSlate();
}

void UDialogueEdFragment_Text::UpdateSlate()
{

	ContextTextEditorContainer->ClearChildren();
	
	if (!GetGraphNodeSlate().IsValid()) return;

	const TSharedPtr<SDialogueGraphNodeBase> NodeSlate = GetGraphNodeSlate().Pin();

	UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>();

	if (CastedNode == nullptr) return;

	const TAttribute<FText> ContextText_Attr = TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateLambda([this]
	{
		if (const UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>()) return CastedNode->Text;

		return FText::GetEmpty();
	}));

	const TAttribute<UDataTable*> TableToEdit_Attr = TAttribute<UDataTable*>::Create(
		TAttribute<UDataTable*>::FGetter::CreateLambda([this]
		{
			UDataTable* Value = nullptr;

			if (const UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>()) Value = CastedNode->GetTextStyleTableIfPresent();
			
			return Value;
		}));

	const TAttribute<bool> bUseStyler_Attr = TAttribute<bool>::Create(
	TAttribute<bool>::FGetter::CreateLambda([this]
	{
		UDataTable* Value = nullptr;

		if (const UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>()) Value = CastedNode->GetTextStyleTableIfPresent();

		return ((Value != nullptr) ? true : false);
		
	}));

	ContextTextEditorContainer->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(ContextTextEditor, SContextTextEditor)
			.Visibility(EVisibility::SelfHitTestInvisible)
			.Text(ContextText_Attr)
			.TableToEdit(TableToEdit_Attr)
			.bUseStyling(bUseStyler_Attr)
			.OnTextChanged_UObject(this, &UDialogueEdFragment_Text::OnTextChange)
			.OnTextCommitted_UObject(this, &UDialogueEdFragment_Text::OnTextCommitted)
		];
}

void UDialogueEdFragment_Text::OnTextChange(const FText& Text)
{
	UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>();

	if (!bHasTransaction)
	{
		GEditor->BeginTransaction(FText::FromString("Modify Context Text"));

		bHasTransaction = true;
	}

	CastedNode->Modify();
	
	const FText SavedText = CastedNode->Text;
	
	FString OutKey, OutNamespace;

	const FString Namespace = FTextInspector::GetNamespace(SavedText).Get(FString());
	const FString Key = FTextInspector::GetKey(SavedText).Get(FString());
	
	//Holds new text and let engine caches this text in.
	FJointEdUtils::DialogueText_StaticStableTextIdWithObj(
		this,
		IEditableTextProperty::ETextPropertyEditAction::EditedSource,
		Text.ToString(),
		Namespace,
		Key,
		OutNamespace,
		OutKey
		);

	CastedNode->Text = FText::ChangeKey(FTextKey(OutNamespace),FTextKey(OutKey),Text);
	
}

void UDialogueEdFragment_Text::OnTextCommitted(const FText& Text, ETextCommit::Type Arg)
{
	UDF_Text* CastedNode = GetCastedNodeInstance<UDF_Text>();

	if (!bHasTransaction)
	{
		GEditor->BeginTransaction(FText::FromString("Modify Context Text"));

		bHasTransaction = true;
	}

	CastedNode->Modify();


	const FText SavedText = CastedNode->Text;
	
	FString OutKey, OutNamespace;

	const FString Namespace = FTextInspector::GetNamespace(SavedText).Get(FString());
	const FString Key = FTextInspector::GetKey(SavedText).Get(FString());

	//Holds new text and let engine caches this text in. This is fundamental when it comes to the 
	FJointEdUtils::DialogueText_StaticStableTextIdWithObj(
		this,
		IEditableTextProperty::ETextPropertyEditAction::EditedSource,
		Text.ToString(),
		Namespace,
		Key,
		OutNamespace,
		OutKey
		);

	CastedNode->Text = FText::ChangeKey(FTextKey(OutNamespace),FTextKey(OutKey),Text);

	if (bHasTransaction)
	{
		GEditor->EndTransaction();

		bHasTransaction = false;
	}
}

FLinearColor UDialogueEdFragment_Text::GetNodeTitleColor() const
{
	return FLinearColor(0.03, 0.03, 0.05, 1);
}

void UDialogueEdFragment_Text::OnNodeInstancePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent,
	const FString& PropertyName)
{
	Super::OnNodeInstancePropertyChanged(PropertyChangedEvent, PropertyName);

	UpdateSlate();
}


#undef LOCTEXT_NAMESPACE
