// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Environment/CBX_GameMode.h"

#include "CBX_GameState.h"
#include "Cubex/Gameplay/Stages/CBX_Stage.h"
#include "Cubex/Player/CBX_Pawn.h"
#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/KismetSystemLibrary.h"

ACBX_GameMode::ACBX_GameMode()
{
	GameplayRound = 1;
	bIsGameEnded = false;
}

void ACBX_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	check(GridClass);
	GridManager = Cast<ACBX_GridManager>(GetWorld()->SpawnActor(GridClass));

	if (GridManager)
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			PC->SetViewTargetWithBlend(GridManager);
			PlayerPawn = Cast<ACBX_Pawn>(PC->GetPawn());
		}
		
		GameplayStage = NewObject<UCBX_Stage>(this, TEXT("GameplayStage"));
		if (GameplayStage)
		{
			GameplayStage->SetGridManager(GridManager);
			GameplayStage->LoadStage(GameplayRound);
		}
	}
	
	CbxGameState = Cast<ACBX_GameState>(GameState);
	CbxGameState->OnDurationFinishedDelegate.AddUniqueDynamic(this, &ACBX_GameMode::Stop);
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
	bIsGameEnded = true;
	ChangeFieldVisibility(false);
	CbxGameState->StopDurationTimer();
	
	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ACBX_Hud* HUD = PC->GetHUD<ACBX_Hud>())
		{
			HUD->ShowRestartGUI();
		}
	}
}

int32 ACBX_GameMode::GetGameplayStateLevel()
{
	return GameplayRound;
}

void ACBX_GameMode::ChangeFieldVisibility(bool bIsVisible)
{
	GridManager->ToggleVisibility(bIsVisible);
	PlayerPawn->Cube->ChangeVisibility(bIsVisible);
}

void ACBX_GameMode::LoadField()
{
	GameplayStage->LoadStage(GameplayRound);
	ChangeFieldVisibility(true);
}

void ACBX_GameMode::NextRound()
{
	GameplayRound++;
}

void ACBX_GameMode::Start()
{
	if (APlayerController* PC = Cast<APlayerController>(PlayerPawn->GetController()))
	{
		if (ACBX_Hud* HUD = Cast<ACBX_Hud>(PC->GetHUD()))
		{
			HUD->ShowGameplayGUI();
		}
	}
	
	CbxGameState->RunStageDurationTimer();
}

void ACBX_GameMode::WaitingToStart()
{
	if (APlayerController* PC = Cast<APlayerController>(PlayerPawn->GetController()))
	{
		if (ACBX_Hud* HUD = Cast<ACBX_Hud>(PC->GetHUD()))
		{
			HUD->ShowPreparationGUI();
		}
	}
}

void ACBX_GameMode::Stop()
{
	if (bIsGameEnded)
	{
		return;
	}
	
	ChangeFieldVisibility(false);
	NextRound();

	if (APlayerController* PC = Cast<APlayerController>(PlayerPawn->GetController()))
	{
		if (ACBX_Hud* HUD = Cast<ACBX_Hud>(PC->GetHUD()))
		{
			HUD->ShowPreparationGUI();
		}
	}
}
