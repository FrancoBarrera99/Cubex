// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Obstacles/CBX_SpykeStrategy.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Cubex/Player/CBX_Pawn.h"

// Sets default values
ACBX_SpykeStrategy::ACBX_SpykeStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	SetRootComponent(RootSceneComponent);
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->InitBoxExtent(FVector(45.0f));
	BoxCollider->SetRelativeLocation(FVector(0.0f,0.0f,100.0f));
	BoxCollider->SetGenerateOverlapEvents(true);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));

}

void ACBX_SpykeStrategy::BuildObstacle(ACBX_GridManager* GridManager)
{
	GridManagerPtr = GridManager;
	
	MoveToEmptyCell();
	PlayAnimation();
}

void ACBX_SpykeStrategy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ACBX_Pawn* Pawn = Cast<ACBX_Pawn>(OtherActor))
	{
		Pawn->Die();
	}
}

void ACBX_SpykeStrategy::UpdateHeight(float HeightOutput)
{
	const FVector NewLocation = FVector(LastLocation.X, LastLocation.Y, LastLocation.Z + HeightOutput);
	StaticMeshComponent->SetRelativeLocation(NewLocation);
}

void ACBX_SpykeStrategy::OnTimelineFinished()
{
	if (GridManagerPtr)
	{
		GridManagerPtr->GetGrid()[SelectedCellIndex]->SetState(ECellState::Empty);
	}
	Destroy();
}

// Called when the game starts or when spawned
void ACBX_SpykeStrategy::BeginPlay()
{
	Super::BeginPlay();

	if (MovementCurve)
	{
		FOnTimelineFloat TimelineFloat;
		FOnTimelineEvent TimelineFinishedEvent;
		
		TimelineFloat.BindDynamic(this, &ACBX_SpykeStrategy::UpdateHeight);
		TimelineComponent->AddInterpFloat(MovementCurve, TimelineFloat);

		TimelineFinishedEvent.BindDynamic(this, &ACBX_SpykeStrategy::OnTimelineFinished);
		TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}
}

void ACBX_SpykeStrategy::MoveToEmptyCell()
{
	if (GridManagerPtr)
	{
		const auto Grid = GridManagerPtr->GetGridByCellState(ECellState::Empty);

		const int32 RandomIndex = FMath::RandRange(0, Grid.Num() - 1);
	
		SelectedCellIndex = Grid[RandomIndex]->GetIndex();
		Grid[SelectedCellIndex]->SetState(ECellState::Obstacle);

		SetActorLocation(Grid[SelectedCellIndex]->GetComponentLocation());
	}
}

void ACBX_SpykeStrategy::PlayAnimation()
{
	LastLocation = StaticMeshComponent->GetRelativeLocation();
	if (TimelineComponent)	TimelineComponent->PlayFromStart();
}


