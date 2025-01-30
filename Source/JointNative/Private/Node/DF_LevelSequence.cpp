//Copyright 2022~2024 DevGrain. All Rights Reserved.


#include "DF_LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/KismetSystemLibrary.h"

UDF_LevelSequence::UDF_LevelSequence()
{
	
}


void UDF_LevelSequence::PostNodeBeginPlay_Implementation()
{

	//If it is null at the first stage, just end it.
	if(SequenceToPlay.IsNull())
	{
		RequestNodeEndPlay();
	}
	
	if (bLoadAsync)
	{
		FSoftObjectPath SequencePath = SequenceToPlay.ToSoftObjectPath();
		
		UAssetManager::GetStreamableManager().RequestAsyncLoad(SequencePath, FStreamableDelegate::CreateUObject(this, &UDF_LevelSequence::ExecuteAction));
	}
	else
	{
		if(SequenceToPlay.Get() == nullptr) SequenceToPlay.LoadSynchronous();
		
		ExecuteAction();
	}
}

void UDF_LevelSequence::ExecuteAction()
{
	if (SequenceToPlay.Get())
	{
		ULevelSequencePlayer::CreateLevelSequencePlayer(this, SequenceToPlay.Get(), PlaybackSettings,
		                                                CreatedLevelSequenceActor);
	}

	RequestNodeEndPlay();
}
