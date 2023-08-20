// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CBX_GameMode.generated.h"

class ACBX_GridManager;
class UCBX_GameContext;
/**
 * 
 */
UCLASS()
class CUBEX_API ACBX_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ACBX_GameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UFUNCTION()
	void EndGame();
	
	UFUNCTION(BlueprintCallable)
	int32 GetGameplayStateLevel();

	UFUNCTION(BlueprintCallable)
	virtual void NextState();

	UFUNCTION(BlueprintCallable)
	virtual void Start();

	UFUNCTION(BlueprintCallable)
	virtual void Stop();

protected:

	UPROPERTY(meta=(MustImplement = "CBX_GameplayState"))
	UObject* CurrentGameplayState;

	UPROPERTY()
	AActor* GridManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> GridClass;
	
};
