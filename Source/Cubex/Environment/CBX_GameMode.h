// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CBX_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CUBEX_API ACBX_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UFUNCTION()
	void EndGame();

	UFUNCTION(BlueprintCallable)
	int32 GetGameStage();
	
};
