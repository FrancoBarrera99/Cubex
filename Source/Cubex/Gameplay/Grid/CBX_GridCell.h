// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CBX_GridCell.generated.h"

UENUM(BlueprintType)
enum ECellState
{
	Empty,
	Obstacle
};

UENUM(BlueprintType)
enum EVisibilityAnimationState
{
	Waiting,
	Showing,
	Hiding,
	Finished
};

/**
 * 
 */
UCLASS()
class CUBEX_API UCBX_GridCell : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UCBX_GridCell();

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SetState(const ECellState& NewCellState);

	UFUNCTION()
	virtual ECellState GetState();

	UFUNCTION()
	virtual void SetIndex(const int32& NewIndex);

	UFUNCTION()
	virtual int32 GetIndex();

	UFUNCTION()
	virtual void ChangeVisibility(bool bIsVisible);

protected:

	UFUNCTION()
	void UpdateScale();

	UFUNCTION()
	void StopUpdatingScale();

	UFUNCTION()
	bool ShouldFinishAnimation() const;

	UPROPERTY()
	float VisibilityAnimationRate;

	UPROPERTY()
	bool bIsUpdating;

	UPROPERTY()
	FTimerHandle VisibilityAnimationTimerHandle;

	UPROPERTY()
	TEnumAsByte<EVisibilityAnimationState> VisibilityAnimationState;

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	TEnumAsByte<ECellState> CellState;
	
};
