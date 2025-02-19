//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Node/JointFragment.h"
#include "DF_LevelSequence.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;
class ULevelSequence;
/**
 * Level Sequence node is a node that spawns a level sequence actor when it is played.
 */
UCLASS(Category = "Joint Native|C++|Sequence", Hidden, meta=(DeprecatedNode, DeprecationMessage="Deprecated on Joint Native 1.2.0. Use the blueprint version of it instead."))
class JOINTNATIVE_API UDF_LevelSequence: public UJointFragment
{
	GENERATED_BODY()

public:

	UDF_LevelSequence();

public:

	virtual void PostNodeBeginPlay_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TSoftObjectPtr<ULevelSequence> SequenceToPlay = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FMovieSceneSequencePlaybackSettings PlaybackSettings;

	/**
	 * Whether to load the level sequence asynchronically or not.
	 * If false, it will try to load the level sequence right away.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	bool bLoadAsync = true;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Data", Transient)
	ALevelSequenceActor* CreatedLevelSequenceActor = nullptr;

public:
	
	UKismetSystemLibrary::FOnAssetLoaded OnSequenceLoadedDele;

	UFUNCTION()
	void ExecuteAction();
};
