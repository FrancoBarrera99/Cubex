// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBX_GridManager.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum ECellState
{
	Empty,
	Obstacle
};

USTRUCT()
struct FCellStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	TEnumAsByte<ECellState> CellState;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
};



UCLASS()
class CUBEX_API ACBX_GridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBX_GridManager();

	const TArray<FCellStruct>& GetGrid();

	TArray<FCellStruct> GetGridByCellState(const ECellState& CellState);

	void ChangeCellState(int32 CellIndex, ECellState NewState);

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

	UPROPERTY()
	TArray<FCellStruct> Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UStaticMesh* GridMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UMaterial* GridMeshMaterial;

	virtual void BeginPlay() override;
	
	void InitializeGrid();
};
