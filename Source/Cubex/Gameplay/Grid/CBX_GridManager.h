// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cubex/Gameplay/Grid/CBX_GridCell.h"
#include "CBX_GridManager.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class CUBEX_API ACBX_GridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBX_GridManager();

	UFUNCTION()
	virtual void UpdateSize(int32 NewGridHeight, int32 NewGridWidth);

	UFUNCTION()
	virtual void ToggleVisibility(bool bIsVisible);

	UFUNCTION()
	TArray<UCBX_GridCell*> GetGrid();

	UFUNCTION()
	TArray<UCBX_GridCell*> GetGridByCellState(const ECellState& CellState);

	UFUNCTION()
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider;

protected:

	UFUNCTION()
	void HideExcessComponents();

	UFUNCTION()
	void ChangeGridComponentsVisibilityInRange(FInt32Range WidthRange, FInt32Range HeightRange, bool bNewVisibility);

	UFUNCTION()
	void UpdateComponents();

	UFUNCTION()
	void CreateNewCellComponent(const FVector& SpawnLocation, int32 CellIndex);

	UPROPERTY()
	bool bIsGridVisible;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridWidth;

	UPROPERTY()
	int32 CellSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStaticMeshComponent> CellClass;

	UPROPERTY()
	TArray<UCBX_GridCell*> Grid;

	virtual void BeginPlay() override;
};
