// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CBX_GameMode.generated.h"

class ACBX_GameState;
class ACBX_Pawn;
class UCBX_Stage;
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

	UFUNCTION(BlueprintNativeEvent)
	AActor* GetGridManager();

	UFUNCTION(BlueprintCallable)
	void ExitGame();
	
	UFUNCTION(BlueprintCallable)
	int32 GetGameplayStateLevel();

	UFUNCTION()
	void ChangeFieldVisibility(bool bIsVisible);

	UFUNCTION(BlueprintCallable)
	void LoadField();
		
	UFUNCTION(BlueprintCallable)
	virtual void WaitingToStart();
	
	UFUNCTION(BlueprintCallable)
	virtual void Start();
	
	UFUNCTION(BlueprintCallable)
	virtual void NextRound();

	UFUNCTION(BlueprintCallable)
	virtual void Stop();
	
	UFUNCTION()
	void EndGame();

protected:

	UPROPERTY()
	int32 GameplayRound;

	UPROPERTY()
	bool bIsGameEnded;

	UPROPERTY()
	UCBX_Stage* GameplayStage;

	UPROPERTY()
	ACBX_GridManager* GridManager;

	UPROPERTY()
	ACBX_GameState* CbxGameState;

	UPROPERTY()
	ACBX_Pawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> GridClass;
	
};
