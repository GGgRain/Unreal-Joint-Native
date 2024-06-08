//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Text.h"
#include "DF_TextStyle.h"

UDF_Text::UDF_Text()
{
#if WITH_EDITORONLY_DATA
	TextStyleInstance.AllowedType.Add(UDF_TextStyle::StaticClass());
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

