// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Cubex/Interfaces/CBX_ObstacleStrategy.h"
#include "GameFramework/Actor.h"
#include "CBX_SpykeStrategy.generated.h"

class FOnTimelineEvent;
class ACBX_Pawn;

UCLASS()
class CUBEX_API ACBX_SpykeStrategy : public AActor, public ICBX_ObstacleStrategy
{
	GENERATED_BODY()
	
public:	
	ACBX_SpykeStrategy();

	virtual void BuildObstacle(ACBX_GridManager* GridManager) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* RootSceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollider;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void MoveToEmptyCell();
	
	UFUNCTION()
	virtual void PlayAnimation();

	UFUNCTION()
	virtual void UpdateHeight(float HeightOutput);

	UFUNCTION()
	virtual void OnTimelineFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACBX_GridManager* GridManagerPtr;

	UPROPERTY()
	int32 SelectedCellIndex;

	UPROPERTY()
	FVector LastLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* TimelineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UCurveFloat* MovementCurve;
};
