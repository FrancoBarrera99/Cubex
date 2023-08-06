// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CBX_Hud.generated.h"

/**
 * 
 */
UCLASS()
class CUBEX_API ACBX_Hud : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowMenuGUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowGameplayGUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowRestartGUI();
	
};
