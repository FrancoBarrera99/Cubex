// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cubex/Interfaces/CBX_ObstacleStrategy.h"
#include "CBX_Stage.generated.h"

/**
 * 
 */
UCLASS()
class CUBEX_API UCBX_Stage : public UObject
{
	GENERATED_BODY()

public:
	UCBX_Stage();

	UFUNCTION()
	void SetGridManager(ACBX_GridManager* NewGridManger);

	UFUNCTION()
	void LoadStage(int32 GameplayRound);

protected:

	UPROPERTY()
	ACBX_GridManager* GridManager;

	UPROPERTY()
	int32 GridSize;
	
};

