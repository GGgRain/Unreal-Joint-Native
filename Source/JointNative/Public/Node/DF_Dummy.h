//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_Dummy.generated.h"

/**
 * Dummy is a 'dummy' fragment that will not play any nodes under itself, and always marked as pending - so it will not block the execution flow.
 * It has been introduced for some special occasions.
 * 
 * It has been initially introduced for level sequencers with Joint Movie track:
 * Because for the nodes that must be played & controlled via the level sequencer, they should never be played by the default playback system, so it must be placed under a Dummy fragment to prevent that.
 * 
 * Note: From Joint Native 2.16.0, Level Sequencer Track Dummy has been renamed to Dummy Fragment for general purposes.
 */
UCLASS(Category = "Joint Native|Common")
class JOINTNATIVE_API UDF_Dummy: public UJointFragment
{
	GENERATED_BODY()

public:

	UDF_Dummy();

public:

	virtual void PostNodeBeginPlay_Implementation() override;

	virtual bool CheckCanMarkNodeAsPending_Implementation() override;
	
};
