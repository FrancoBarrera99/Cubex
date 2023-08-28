// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Stages/CBX_Stage.h"

#include "Cubex/Environment/CBX_GameState.h"
#include "Cubex/Gameplay/Obstacles/CBX_SpykeStrategy.h"
#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/GameplayStatics.h"

UCBX_Stage::UCBX_Stage()
{
	GridSize = 1;
}

void UCBX_Stage::SetGridManager(ACBX_GridManager* NewGridManger)
{
	GridManager = NewGridManger;
}

void UCBX_Stage::LoadStage(int32 GameplayRound)
{
	//TODO: read Table

	GridSize += 2;
	if (ACBX_GameState* CbxGameState = Cast<ACBX_GameState>(GetWorld()->GetGameState())) CbxGameState->UpdateStageDuration(10);
	GridManager->UpdateSize(GridSize, GridSize);
}