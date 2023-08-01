// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBX_GridManager.generated.h"

class UCameraComponent;
class USpringArmComponent;


UENUM(BlueprintType)
enum ECellState
{
	Empty,
	Obstacle
};

UCLASS()
class CUBEX_API ACBX_GridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBX_GridManager();

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
	TArray<TEnumAsByte<ECellState>> GridState;

	UPROPERTY()
	TArray<UStaticMeshComponent*> ManagedStaticMeshComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UStaticMesh* GridMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UMaterial* GridMeshMaterial;

	virtual void BeginPlay() override;
	
	void InitializeGrid();
};
