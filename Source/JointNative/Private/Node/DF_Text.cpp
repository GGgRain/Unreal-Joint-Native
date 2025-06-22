//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "Node/DF_Text.h"
#include "Node/DF_TextStyle.h"

#include "JointVersionComparison.h"

UDF_Text::UDF_Text()
{
#if WITH_EDITORONLY_DATA

	TextStyleInstance.AllowedType.Add(UDF_TextStyle::StaticClass());

#if JOINT_VERSION_OLDER_THAN(2, 9, 0)
	
	bAllowDisplayClassFriendlyNameText = false;
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Maximum;

#else

	EdNodeSetting.bAllowDisplayClassFriendlyNameText = false;
	EdNodeSetting.DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Maximum;

#endif

#endif
}

const FText UDF_Text::GetText_Implementation() const
{
	return Text;
}

void UDF_Text::SetText_Implementation(const FText& InText)
{
	Text = InText;
}

UDataTable* UDF_Text::GetTextStyleTableIfPresent_Implementation() const
{
	if (UDF_TextStyle* Node = RESOLVE_JOINT_POINTER(TextStyleInstance, UDF_TextStyle))
	{
		return Cast<UDF_TextStyle>(TextStyleInstance.Node.Get())->TextStyleTable;
	}

	return nullptr;
}
