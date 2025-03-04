//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_Branch.h"
#include "DF_Condition.h"

UDF_Branch::UDF_Branch()
{
	//Condition node is a decorator node.
	//NodeTags.AddTag(SDS_NodeTag_Decorator);
	
	//Condition node can be attached anywhere.
}

TArray<UJointNodeBase*> UDF_Branch::SelectNextNodes_Implementation(AJointActor* InHostingDialogueInstance)
{

	if(!IsNodeBegunPlay())
	{
		return TArray<UJointNodeBase*>();
	}
	
	UJointFragment* Condition = FindFragmentByClass(UDF_Condition::StaticClass());

	if(Condition)
	{
		UDF_Condition* CastedCondition = Cast<UDF_Condition>(Condition);
		
		if(CastedCondition->bConditionResult)
		{
			return TrueNode;
		}else
		{
			if(UJointFragment* ChildBranch = FindFragmentByClass(UDF_Branch::StaticClass()))
			{
				return ChildBranch->SelectNextNodes(InHostingDialogueInstance);
			}

			if(bUseFalse)
			{
				return FalseNode;
			}

			return TArray<UJointNodeBase*>();
		}
	}
	
	return TrueNode;
}
