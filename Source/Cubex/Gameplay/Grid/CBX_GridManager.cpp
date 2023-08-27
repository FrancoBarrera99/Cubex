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
	GridHeight = GridWidth = 0;
	CellSpace = 100;

	//Root Comp
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(SceneComponent);

	//Box collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->InitBoxExtent(FVector(0.0));
	BoxCollider->SetGenerateOverlapEvents(true);

	//Camera Setup
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 175.0f * GridHeight;
	SpringArmComponent->SetRelativeRotation(FRotator(-30,-135, 0));
	CameraComponent->SetupAttachment(SpringArmComponent);

	bIsGridVisible = false;
	
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

void ACBX_GridManager::UpdateSize(int32 NewGridHeight, int32 NewGridWidth)
{
    if (NewGridHeight == GridHeight && NewGridWidth == GridWidth)
    {
        return;
    }

    GridHeight = NewGridHeight;
    GridWidth = NewGridWidth;

    UpdateComponents();
}

void ACBX_GridManager::ToggleVisibility(bool bIsVisible)
{
	if (bIsVisible == bIsGridVisible)
	{
		return;
	}
	
	bIsGridVisible = !bIsGridVisible;
	
	const FInt32Range WidthRange(0, GridWidth);
	const FInt32Range HeightRange(0, GridHeight);

	ChangeGridComponentsVisibilityInRange(WidthRange, HeightRange, bIsVisible);
}

void ACBX_GridManager::HideExcessComponents()
{
	const FInt32Range WidthRange(GridWidth, Grid.Num());
	const FInt32Range HeightRange(GridHeight, Grid.Num());

	ChangeGridComponentsVisibilityInRange(WidthRange, HeightRange, false);
}

void ACBX_GridManager::ChangeGridComponentsVisibilityInRange(FInt32Range WidthRange, FInt32Range HeightRange,
	bool bNewVisibility)
{
	for (int i = WidthRange.GetLowerBoundValue(); i < WidthRange.GetUpperBoundValue(); ++i)
	{
		for (int j = HeightRange.GetLowerBoundValue(); j < HeightRange.GetUpperBoundValue(); ++j)
		{
			const int32 ComponentIndex = i * GridHeight + j;
			if (ComponentIndex >= 0 && ComponentIndex < Grid.Num())
			{
				if (UCBX_GridCell* GridCellComponent = Grid[ComponentIndex])
				{
					GridCellComponent->ChangeVisibility(bNewVisibility);
				}
			}
		}
	}
}

void ACBX_GridManager::UpdateComponents()
{
	const float HalfWidth = (GridWidth - 1) * CellSpace * 0.5f;
	const float HalfHeight = (GridHeight - 1) * CellSpace * 0.5f;
	
	BoxCollider->SetBoxExtent(FVector(HalfWidth, HalfHeight,  CellSpace * 2));
	SpringArmComponent->TargetArmLength = 175.0f * GridHeight;

	int32 CellIndex = 0;

	for (int w = 0; w < GridWidth; ++w)
	{
		for (int h = 0; h < GridHeight; ++h)
		{
			const int32 ComponentIndex = w * GridHeight + h;
			const FVector ComponentLocation = FVector(w * CellSpace - HalfWidth, h * CellSpace - HalfHeight, 0.0f);

			if (ComponentIndex >= Grid.Num())
			{
				CreateNewCellComponent(ComponentLocation, CellIndex);
			}
			else
			{
				if (UCBX_GridCell* GridCellComponent = Grid[ComponentIndex])
				{
					GridCellComponent->SetRelativeLocation(ComponentLocation);
					GridCellComponent->SetIndex(ComponentIndex);
				}
			}

			CellIndex++;
		}
	}
}


void ACBX_GridManager::CreateNewCellComponent(const FVector& SpawnLocation, int32 CellIndex)
{
	const FName ComponentName = FName(TEXT("GridCellComponent") + FString::FromInt(CellIndex));

	if (UCBX_GridCell* GridCellComponent = NewObject<UCBX_GridCell>(this, CellClass, ComponentName))
	{
		GridCellComponent->RegisterComponent();
		GridCellComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		GridCellComponent->SetRelativeLocation(SpawnLocation);
		GridCellComponent->SetRelativeScale3D(FVector(0.1f));
		GridCellComponent->SetIndex(CellIndex);

		Grid.Add(GridCellComponent);
	}
}


