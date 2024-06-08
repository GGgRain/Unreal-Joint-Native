//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "JointNativeEditor.h"

#define LOCTEXT_NAMESPACE "JointNativeEditor"


void FJointNativeEditorModule::StartupModule()
{

}

void FJointNativeEditorModule::ShutdownModule()
{
}

bool FJointNativeEditorModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FJointNativeEditorModule, JointNativeEditor)
