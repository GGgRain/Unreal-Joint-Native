//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "Editor/JointManagementTabs_Native.h"

#include "Editor/Slate/JointAdvancedWidgets.h"
#include "Editor/Style/JointEditorStyle.h"

#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "FJointManagementTab_JointNativeUtility"


FJointManagementTab_JointNativeUtility::FJointManagementTab_JointNativeUtility() : IJointManagementSubTab()
{
}

FJointManagementTab_JointNativeUtility::~FJointManagementTab_JointNativeUtility()
{
}

TSharedRef<IJointManagementSubTab> FJointManagementTab_JointNativeUtility::MakeInstance()
{
	return MakeShareable(new FJointManagementTab_JointNativeUtility);
}

void FJointManagementTab_JointNativeUtility::RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager)
{
	TabManager->RegisterTabSpawner(
			GetTabId()
			, FOnSpawnTab::CreateLambda(
				[=](const FSpawnTabArgs&)
				{
					return SNew(SDockTab)
						.TabRole(ETabRole::PanelTab)
						.Label(LOCTEXT("JointYggdrasilUtility", "Joint Native Utility"))
						[
							SNew(SJointNativeTab)
						];
				}
			)
		)
		.SetDisplayName(LOCTEXT("EditorUtilityTabTitle", "Joint Native Utility"))
		.SetTooltipText(LOCTEXT("EditorUtilityTooltipText", "Open the Joint Native Utility tab."))
		.SetIcon(FSlateIcon(FJointEditorStyle::GetUEEditorSlateStyleSetName(), "ExternalImagePicker.GenerateImageButton"));
}

const FName FJointManagementTab_JointNativeUtility::GetTabId()
{
	return "TAB_JointNativeUtility";
}

const ETabState::Type FJointManagementTab_JointNativeUtility::GetInitialTabState()
{
	return IJointManagementSubTab::GetInitialTabState();
}

#if UE_VERSION_OLDER_THAN(5,1,0)

#include "AssetRegistryModule.h"
#include "ARFilter.h"

#else

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/ARFilter.h"

#endif


TSharedRef<SWidget> SJointNativeTab::CreateProductSection()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FJointEditorStyle::Margin_Border)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.TextStyle(FJointEditorStyle::Get(), "JointUI.TextBlock.Regular.h5")
			.Text(LOCTEXT("DescText", "Joint Native, the official dialogue related content plugin for Joint framework"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FJointEditorStyle::Margin_Border)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.TextStyle(FJointEditorStyle::Get(), "JointUI.TextBlock.Regular.h5")
			.Text(LOCTEXT("CopyrightText", "Copyright 2022~2025 DevGrain. All Rights Reserved."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FJointEditorStyle::Margin_Border)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.TextStyle(FJointEditorStyle::Get(), "JointUI.TextBlock.Regular.h5")
			.Text(LOCTEXT("LicenseText", "Joint Native is licensed under Apache License 2.0."))
		];
}

void SJointNativeTab::Construct(const FArguments& InArgs)
{
	ChildSlot.DetachWidget();

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FJointEditorStyle::Get().GetBrush("JointUI.Image.GraphBackground"))
		.Padding(FJointEditorStyle::Margin_Border)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Top)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			.Padding(FJointEditorStyle::Margin_Border)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				CreateProductSection()
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE
