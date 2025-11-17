//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_LevelSequenceTrackDummy.generated.h"

/**
 * Level Sequencer Track Dummy is a dummy fragment for the Joint Level Sequencer Track.
 * It simply just, don't play any nodes under itself, and always marked as pending.
 *
 * It has been introduced for some special occasions. If you do not want to place your nodes on the SpawnLevelSequence, or WaitUntilLevelSequenceEnd fragment, you need a dummy one that will not interrupt the playback - in the case, it comes handy.
 *
 * If possible, just put your nodes under the SpawnLevelSequence or WaitUntilLevelSequenceEnd fragment, instead of using this dummy one - it will make your graph cleaner and use less resources.
 */
UCLASS(Category = "Joint Native|Level Sequence")
class JOINTNATIVE_API UDF_LevelSequenceTrackDummy: public UJointFragment
{
	GENERATED_BODY()

public:

	UDF_LevelSequenceTrackDummy();

public:

	virtual void PostNodeBeginPlay_Implementation() override;

	virtual bool CheckCanMarkNodeAsPending_Implementation() override;
	
};
