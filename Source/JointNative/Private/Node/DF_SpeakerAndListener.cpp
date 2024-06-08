//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DF_SpeakerAndListener.h"

#include "DF_Participant.h"

UDF_SpeakerAndListener::UDF_SpeakerAndListener()
{

}

TArray<UDF_Participant*> UDF_SpeakerAndListener::GetAllSpeakers()
{
	TArray<UDF_Participant*> OutArray;
	
	for (FDialogueNodePointer Speaker : Speakers)
	{
		if(Speaker.Node == nullptr)continue;
		
		if(UDF_Participant* Participant = Cast<UDF_Participant>(Speaker.Node.Get()))
		{
			OutArray.Add(Participant);
		}
	}

	return OutArray;
}

TArray<UDF_Participant*> UDF_SpeakerAndListener::GetAllListeners()
{
	TArray<UDF_Participant*> OutArray;
	
	for (FDialogueNodePointer Listener : Listeners)
	{
		if(Listener.Node == nullptr)continue;
		
		if(UDF_Participant* Participant = Cast<UDF_Participant>(Listener.Node.Get()))
		{
			OutArray.Add(Participant);
		}
	}

	return OutArray;

}
