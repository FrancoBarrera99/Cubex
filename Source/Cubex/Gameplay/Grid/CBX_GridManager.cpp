// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Grid/CBX_GridManager.h"

#include "CBX_GridCell.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Cubex/Interfaces/CBX_GridMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACBX_GridManager::ACBX_GridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Grid values
	GridHeight = GridWidth = 9;
	CellSpace = 100;

	//Root Comp
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(SceneComponent);

	//Box collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->InitBoxExtent(FVector(GridWidth * (CellSpace / 2) - 1,GridHeight * (CellSpace / 2) - 1,  CellSpace * 2));
	BoxCollider->SetGenerateOverlapEvents(true);

	//Camera Setup
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 175.0f * GridHeight;
	SpringArmComponent->SetRelativeRotation(FRotator(-30,-135, 0));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

TArray<UCBX_GridCell*> ACBX_GridManager::GetGrid()
{
	return Grid;
}

TArray<UCBX_GridCell*> ACBX_GridManager::GetGridByCellState(const ECellState& CellState)
{
	return Grid.FilterByPredicate([CellState](UCBX_GridCell* CellComponent)
	{
		return CellComponent->GetState() == CellState;
	});
}

void ACBX_GridManager::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (Cast<ICBX_GridMovement>(OtherActor))	Cast<ICBX_GridMovement>(OtherActor)->OutOfBounds();
}

void ACBX_GridManager::BeginPlay()
{
	Super::BeginPlay();
}

void ACBX_GridManager::BuildGrid()
{
		const float HalfWidth = (GridWidth - 1) * CellSpace * 0.5f;
		const float HalfHeight = (GridHeight - 1) * CellSpace * 0.5f;
		int32 CellIndex = 0;

		for (int i = 0; i < GridWidth; ++i)
		{
			for (int j = 0; j < GridHeight; ++j)
			{
				// Calculate the offset from the center for each cell
				const float OffsetX = i * CellSpace - HalfWidth;
				const float OffsetY = j * CellSpace - HalfHeight;

				const FVector SpawnLocation = FVector(OffsetX, OffsetY, 0.0f);
				const FName ComponentName = FName(TEXT("GridCellComponent") + FString::FromInt(i * GridHeight + j));

				if (UCBX_GridCell* GridCellComponent = NewObject<UCBX_GridCell>(this, CellClass, ComponentName))
				{
					GridCellComponent->RegisterComponent();
					GridCellComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
					GridCellComponent->SetRelativeLocation(SpawnLocation);
					GridCellComponent->SetIndex(CellIndex);
				
					Grid.Add(GridCellComponent);
				}
				CellIndex++;
			}
		}
}



