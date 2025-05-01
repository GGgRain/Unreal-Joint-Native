//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DF_TextStyle.h"

#include "JointVersionComparison.h"

UDF_TextStyle::UDF_TextStyle()
{

#if WITH_EDITORONLY_DATA

#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.00, 0.0,0.00, 0.700000);
	
#else

	EdNodeSetting.bUseSpecifiedGraphNodeBodyColor = true;
	EdNodeSetting.NodeBodyColor = FLinearColor(0.00, 0.0,0.00, 0.700000);
	
#endif
	
#endif
	
	
}

