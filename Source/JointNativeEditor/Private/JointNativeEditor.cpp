//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "JointNativeEditor.h"

#include "JointEditor.h"
#include "Editor/JointManagementTabs_Native.h"
#include "Editor/Management/JointManagement.h"
#include "Node/DF_SpeakerAndListener.h"

#define LOCTEXT_NAMESPACE "JointNativeEditor"


void FJointNativeEditorModule::StartupModule()
{
	
	FJointEditorModule& EditorModule = FModuleManager::GetModuleChecked<FJointEditorModule>("JointEditor");

	EditorModule.JointManagementTabHandler->AddSubTab(FJointManagementTab_JointNativeUtility::MakeInstance());

	RegisterClassLayout();

}


void FJointNativeEditorModule::ShutdownModule()
{
	UnregisterClassLayout();
}

void FJointNativeEditorModule::RegisterClassLayout()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//Class Detail Customization
	
}

void FJointNativeEditorModule::UnregisterClassLayout()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
}



bool FJointNativeEditorModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE
