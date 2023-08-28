// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CBX_AnimatedStaticMeshComponent.generated.h"

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
class CUBEX_API UCBX_AnimatedStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UCBX_AnimatedStaticMeshComponent();

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
	FTimerHandle VisibilityAnimationTimerHandle;

	UPROPERTY()
	TEnumAsByte<EVisibilityAnimationState> VisibilityAnimationState;
	
};
