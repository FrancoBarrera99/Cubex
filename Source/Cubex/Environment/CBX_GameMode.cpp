// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Environment/CBX_GameMode.h"

#include "Cubex/UI/CBX_Hud.h"
#include "Kismet/KismetSystemLibrary.h"

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
}

int32 ACBX_GameMode::GetGameStage()
{
	return 1;
}
