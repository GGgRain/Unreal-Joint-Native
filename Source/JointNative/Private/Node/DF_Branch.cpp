//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Branch.h"
#include "DF_Condition.h"

UDF_Branch::UDF_Branch()
{
	//Condition node is a decorator node.
	//NodeTags.AddTag(SDS_NodeTag_Decorator);
	
	//Condition node can be attached anywhere.
}

TArray<UDialogueNodeBase*> UDF_Branch::SelectNextNodes_Implementation(const TSoftObjectPtr<ADialogueActor>& InHostingDialogueInstance)
{

	if(!IsNodeBegunPlay())
	{
		return TArray<UDialogueNodeBase*>();
	}
	
	UDialogueFragment* Condition = FindFragmentByClass(UDF_Condition::StaticClass());

	if(Condition)
	{
		UDF_Condition* CastedCondition = Cast<UDF_Condition>(Condition);
		
		if(CastedCondition->bConditionResult)
		{
			return TrueNode;
		}else
		{
			if(UDialogueFragment* ChildBranch = FindFragmentByClass(UDF_Branch::StaticClass()))
			{
				return ChildBranch->SelectNextNodes(InHostingDialogueInstance);
			}

			if(bUseFalse)
			{
				return FalseNode;
			}

			return TArray<UDialogueNodeBase*>();
		}
	}
	
	return TrueNode;
}
