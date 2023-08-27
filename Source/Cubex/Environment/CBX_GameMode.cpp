// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Environment/CBX_GameMode.h"

#include "Cubex/Gameplay/Stages/CBX_Stage.h"
#include "Cubex/Interfaces/CBX_GameplayState.h"
#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/KismetSystemLibrary.h"

ACBX_GameMode::ACBX_GameMode()
{
}

void ACBX_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	check(GridClass);
	GridManager = GetWorld()->SpawnActor(GridClass);
	
	check(Cast<ACBX_GridManager>(GridManager))
	CurrentGameplayState = NewObject<UCBX_Stage>(this);
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->SetGridManager(Cast<ACBX_GridManager>(GridManager));
	}
	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetViewTargetWithBlend(GridManager);
	}
}

AActor* ACBX_GameMode::GetGridManager_Implementation()
{
	return GridManager;
}

void ACBX_GameMode::ExitGame()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController()) UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, false);
}

void ACBX_GameMode::EndGame()
{
	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ACBX_Hud* HUD = PC->GetHUD<ACBX_Hud>())
		{
			HUD->ShowRestartGUI();
		}
	}
	Stop();
}

int32 ACBX_GameMode::GetGameplayStateLevel()
{
	int32 Level = 0;
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Level = Cast<ICBX_GameplayState>(CurrentGameplayState)->GetLevel();
	}
	return Level;
}

void ACBX_GameMode::NextState()
{
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->NextState();
	}
}

void ACBX_GameMode::Start()
{
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->Start();
	}
}

void ACBX_GameMode::WaitingToStart()
{
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->WaitingToStart();
	}
}

void ACBX_GameMode::Stop()
{
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->Stop();
	}
}
