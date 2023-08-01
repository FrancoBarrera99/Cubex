// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/CBX_GridManager.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACBX_GridManager::ACBX_GridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Grid values
	GridHeight = GridWidth = 15;
	CellSpace = 100;
	GridState.Init(ECellState::Empty, GridHeight * GridWidth);

	//Root Comp
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(SceneComponent);

	//Camera Setup
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 175.0f * GridHeight;
	SpringArmComponent->SetRelativeRotation(FRotator(-30,-135, 0));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

void ACBX_GridManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid();
}

void ACBX_GridManager::InitializeGrid()
{
	if (GridMesh)
	{
		if (GridMeshMaterial)
		{
			GridMesh->SetMaterial(0, GridMeshMaterial);
		}

		const float HalfWidth = (GridWidth - 1) * CellSpace * 0.5f;
		const float HalfHeight = (GridHeight - 1) * CellSpace * 0.5f;

		for (int i = 0; i < GridWidth; ++i)
		{
			for (int j = 0; j < GridHeight; ++j)
			{
				// Calculate the offset from the center for each cell
				float OffsetX = i * CellSpace - HalfWidth;
				float OffsetY = j * CellSpace - HalfHeight;

				const FVector SpawnLocation = FVector(OffsetX, OffsetY, 0.0f);
				const FName MeshName = FName(TEXT("StaticMeshComponent_") + FString::FromInt(i * GridHeight + j));
				
				UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, MeshName);
				this->AddInstanceComponent(StaticMeshComponent);
				StaticMeshComponent->RegisterComponent();
				this->Modify();
				ManagedStaticMeshComponents.Add(StaticMeshComponent);

				StaticMeshComponent->SetStaticMesh(GridMesh);
				StaticMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
				StaticMeshComponent->SetRelativeLocation(SpawnLocation);
			}
		}
	}
}


