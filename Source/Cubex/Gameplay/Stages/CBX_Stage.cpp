// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Stages/CBX_Stage.h"

#include "Cubex/Gameplay/Obstacles/CBX_SpykeStrategy.h"
#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/GameplayStatics.h"

UCBX_Stage::UCBX_Stage()
{
	Level = 0;
	SpawnRate = 2.0f;
	Duration = ElapsedDuration = 20.0f;
	ObstaclesIncludedIndex = 0;

	ObstaclesClasses.Add(ACBX_SpykeStrategy::StaticClass());
}

void UCBX_Stage::Start()
{
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &UCBX_Stage::ControlStageDuration, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &UCBX_Stage::ControlObstacleSpawning, SpawnRate, true);
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (ACBX_Hud* HUD = Cast<ACBX_Hud>(PC->GetHUD()))
		{
			HUD->ShowGameplayGUI();
		}
	}
}

void UCBX_Stage::NextState()
{
	Level++;
	SpawnRate *= 0.95f;
	Duration *= 1.1f;
	ElapsedDuration = Duration;

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (ACBX_Hud* HUD = Cast<ACBX_Hud>(PC->GetHUD()))
		{
			HUD->ShowPreparationGUI();
		}
	}
}

void UCBX_Stage::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
}

int32 UCBX_Stage::GetLevel()
{
	return Level;
}

void UCBX_Stage::ControlStageDuration()
{
	if (ElapsedDuration == 0)
	{
		Stop();
		NextState();
		return;
	}

	ElapsedDuration--;
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Stage Duration: %d"), ElapsedDuration));
}

void UCBX_Stage::ControlObstacleSpawning()
{
	
}
