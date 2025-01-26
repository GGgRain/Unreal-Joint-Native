//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_TextStyle.h"

UDF_TextStyle::UDF_TextStyle()
{

#if WITH_EDITORONLY_DATA

	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.00, 0.0,0.00, 0.700000);
	
#endif
	
}

