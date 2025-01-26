//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Text.h"
#include "DF_TextStyle.h"

UDF_Text::UDF_Text()
{
#if WITH_EDITORONLY_DATA
	bAllowDisplayClassFriendlyNameText = false;
	TextStyleInstance.AllowedType.Add(UDF_TextStyle::StaticClass());
	DefaultEdSlateDetailLevel = EDialogueEdSlateDetailLevel::SlateDetailLevel_Maximum;

	// bUseSpecifiedGraphNodeBodyColor = false;
	// NodeBodyColor = FLinearColor(
	// 4.4f / 255.f,
	// 4.4f / 255.f,
	// 5.1f / 255.f,
	// 255.f / 255.f);
	
#endif
}

UDataTable* UDF_Text::GetTextStyleTableIfPresent() const
{
	if(TextStyleInstance.Node)
	{
		if(Cast<UDF_TextStyle>(TextStyleInstance.Node.Get()))
		{
			return Cast<UDF_TextStyle>(TextStyleInstance.Node.Get())->TextStyleTable;
		}
	}

	return nullptr;
}

