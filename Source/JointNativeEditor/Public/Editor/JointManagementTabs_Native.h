//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Management/JointManagement.h"


class JOINTNATIVEEDITOR_API FJointManagementTab_JointNativeUtility: public IJointManagementSubTab
{

public:
	
	FJointManagementTab_JointNativeUtility();

	virtual ~FJointManagementTab_JointNativeUtility() override;

public:

	static TSharedRef<IJointManagementSubTab> MakeInstance();

public:
	
	virtual void RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager) override;

public:

	virtual const FName GetTabId() override;

	virtual const ETabState::Type GetInitialTabState() override;
	
};

/**
 * Content widget for the FJointManagementTab_JointNativeUtility. it's just a pure slate. make something like this for your own extension.
 */
class JOINTNATIVEEDITOR_API SJointNativeTab : public SCompoundWidget
{
	
public:

	SLATE_BEGIN_ARGS(SJointNativeTab) {}
	SLATE_END_ARGS();
	
	void Construct(const FArguments& InArgs);

public:

	TSharedRef<SWidget> CreateProductSection();
	
};
