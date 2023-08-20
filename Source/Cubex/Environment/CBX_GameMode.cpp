// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Environment/CBX_GameMode.h"

#include "Cubex/Gameplay/Stages/CBX_Stage.h"
#include "Cubex/Interfaces/CBX_GameplayState.h"
#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/KismetSystemLibrary.h"

ACBX_GameMode::ACBX_GameMode()
{
	//CurrentGameplayState = CreateDefaultSubobject<UCBX_Stage>(TEXT("Stage"));
}

void ACBX_GameMode::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameplayState = NewObject<UCBX_Stage>(this);

	if (GridClass)
	{
		GridManager = GetWorld()->SpawnActor(GridClass);
	}
	if (Cast<ACBX_GridManager>(GridManager))
	{
		Cast<ACBX_GridManager>(GridManager)->BuildGrid();
	}
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetViewTargetWithBlend(GridManager);
	}
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

void ACBX_GameMode::Stop()
{
	if (Cast<ICBX_GameplayState>(CurrentGameplayState))
	{
		Cast<ICBX_GameplayState>(CurrentGameplayState)->Stop();
	}
}
