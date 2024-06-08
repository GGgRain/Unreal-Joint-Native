//Copyright 2022~2024 DevGrain. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Modules/ModuleInterface.h"

class FJointNativeEditorModule : 
	public IModuleInterface
{
public:

	//~ IModuleInterface interface

	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override;
};

//IMPLEMENT_MODULE(FJointEditorModule, JointEditor)

