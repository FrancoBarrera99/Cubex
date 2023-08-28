// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CBX_GameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElapsedDurationChangedSignature, int32, ElapsedDuration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDurationFinishedSignature);


/**
 * 
 */
UCLASS()
class CUBEX_API ACBX_GameState : public AGameStateBase
{
	GENERATED_BODY()
public:

	ACBX_GameState();
	
	UFUNCTION()
	void RunStageDurationTimer();

	UFUNCTION()
	void UpdateStageDuration(int32 NewDuration);
	
	UFUNCTION()
	void StopDurationTimer();

	UPROPERTY(BlueprintAssignable)
	FOnElapsedDurationChangedSignature OnElapsedDurationChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDurationFinishedSignature OnDurationFinishedDelegate;

private:
	
	UFUNCTION()
	void ControlStageDuration();
	
	UPROPERTY()
	int32 Duration;
	
	UPROPERTY()
	int32 ElapsedDuration;

	UPROPERTY()
	FTimerHandle StageDurationHandle;
	
};
