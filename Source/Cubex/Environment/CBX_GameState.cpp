// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Environment/CBX_GameState.h"

#include "CBX_GameMode.h"

ACBX_GameState::ACBX_GameState()
{
	Duration = ElapsedDuration = 0;
}

void ACBX_GameState::RunStageDurationTimer()
{
	ElapsedDuration = Duration;
	OnElapsedDurationChangedDelegate.Broadcast(ElapsedDuration);
	GetWorld()->GetTimerManager().SetTimer(StageDurationHandle, this, &ACBX_GameState::ControlStageDuration, 1.0f, true);
}

void ACBX_GameState::UpdateStageDuration(int32 NewDuration)
{
	Duration = NewDuration;
}

void ACBX_GameState::ControlStageDuration()
{
	if (ElapsedDuration <= 1)
	{
		StopDurationTimer();
		return;
	}

	ElapsedDuration--;
	OnElapsedDurationChangedDelegate.Broadcast(ElapsedDuration);
}

void ACBX_GameState::StopDurationTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(StageDurationHandle);
	OnDurationFinishedDelegate.Broadcast();
}
