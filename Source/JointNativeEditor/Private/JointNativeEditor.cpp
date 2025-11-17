//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "JointNativeEditor.h"

#include "ISequencerModule.h"
#include "JointEditor.h"
#include "PropertyEditorModule.h"
#include "Editor/JointManagementTabs_Native.h"
#include "Editor/Management/JointManagement.h"
#include "Editor/Sequencer/JointMovieTrackEditor.h"
#include "Node/DF_SpeakerAndListener.h"

#include "SequencerChannelInterface.h"


#define LOCTEXT_NAMESPACE "JointNativeEditor"


void FJointNativeEditorModule::StartupModule()
{

	if (FJointEditorModule* EditorModule = FJointEditorModule::Get())
	{
		EditorModule->JointManagementTabHandler->AddSubTab(FJointManagementTab_JointNativeUtility::MakeInstance());
	}
	
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

IMPLEMENT_MODULE(FJointNativeEditorModule, JointNativeEditor)

#undef LOCTEXT_NAMESPACE
