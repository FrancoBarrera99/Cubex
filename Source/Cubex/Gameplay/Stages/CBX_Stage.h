// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cubex/Interfaces/CBX_GameplayState.h"
#include "Cubex/Interfaces/CBX_ObstacleStrategy.h"
#include "UObject/NoExportTypes.h"
#include "CBX_Stage.generated.h"

DECLARE_DELEGATE(FDurationFinished);
DECLARE_DELEGATE(FSpawnFinished);

/**
 * 
 */
UCLASS()
class CUBEX_API UCBX_Stage : public UObject, public ICBX_GameplayState
{
	GENERATED_BODY()

public:
	UCBX_Stage();

	virtual void SetGridManager(ACBX_GridManager* NewGridManger) override;
	virtual void WaitingToStart() override;
	virtual void Start() override;
	virtual void NextState() override;
	virtual void Stop() override;
	virtual int32 GetLevel() override;

protected:

	void ControlStageDuration();

	void ControlObstacleSpawning();

	UPROPERTY()
	ACBX_GridManager* GridManager;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 GridSize;

	UPROPERTY()
	TArray<ICBX_ObstacleStrategy*> ObstaclesObjects;

	UPROPERTY(meta=(MustImplement = "CBX_ObstacleStrategy"))
	TArray<TSubclassOf<ICBX_ObstacleStrategy>> ObstaclesClasses;

	UPROPERTY()
	int32 ObstaclesIncludedIndex;

	UPROPERTY()
	float SpawnRate;

	UPROPERTY()
	int32 ElapsedDuration;

	UPROPERTY()
	float Duration;

	UPROPERTY()
	FTimerHandle DurationHandle;

	UPROPERTY()
	FTimerHandle SpawnHandle;
};
