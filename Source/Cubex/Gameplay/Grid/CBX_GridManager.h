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

	void BuildGrid();

	TArray<UCBX_GridCell*> GetGrid();

	TArray<UCBX_GridCell*> GetGridByCellState(const ECellState& CellState);

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider;

protected:

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
