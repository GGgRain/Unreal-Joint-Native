//Copyright 2022~2024 DevGrain. All Rights Reserved.

#include "DF_SpeakerAndListener.h"

#include "DF_Participant.h"

UDF_SpeakerAndListener::UDF_SpeakerAndListener()
{
#if WITH_EDITORONLY_DATA

	bUseSpecifiedGraphNodeBodyColor = true;
	NodeBodyColor = FLinearColor(0.05f, 0.15f, 0.2f, 0.4);
	DefaultEdSlateDetailLevel = EJointEdSlateDetailLevel::SlateDetailLevel_Minimal_Content;

#endif
}

TArray<UDF_Participant*> UDF_SpeakerAndListener::GetSpeakerParticipants()
{
	TArray<UDF_Participant*> OutArray;
	
	for (FJointNodePointer Speaker : Speakers)
	{
		if(Speaker.Node == nullptr)continue;
		
		if(UDF_Participant* Participant = Cast<UDF_Participant>(Speaker.Node.Get()))
		{
			OutArray.Add(Participant);
		}
	}

	return OutArray;
}

TArray<UDF_Participant*> UDF_SpeakerAndListener::GetListenerParticipants()
{
	TArray<UDF_Participant*> OutArray;
	
	for (FJointNodePointer Listener : Listeners)
	{
		if(Listener.Node == nullptr)continue;
		
		if(UDF_Participant* Participant = Cast<UDF_Participant>(Listener.Node.Get()))
		{
			OutArray.Add(Participant);
		}
	}

	return OutArray;

}

TArray<FJointNodePointer> UDF_SpeakerAndListener::GetSpeakers()
{
	return Speakers;
}

TArray<FJointNodePointer> UDF_SpeakerAndListener::GetListeners()
{
	return Listeners;
}


void UDF_SpeakerAndListener::SetSpeakers(TArray<FJointNodePointer> InSpeakers)
{
	Speakers = InSpeakers;
}

void UDF_SpeakerAndListener::SetListeners(TArray<FJointNodePointer> InListeners)
{
	Listeners = InListeners;
}
