// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Cubex/Interfaces/CBX_GridMovement.h"
#include "GameFramework/Pawn.h"
#include "CBX_Pawn.generated.h"

class UCBX_AnimatedStaticMeshComponent;
class UInputAction;

DECLARE_DELEGATE(FMovementFinished);

UCLASS()
class CUBEX_API ACBX_Pawn : public APawn, public ICBX_GridMovement
{
	GENERATED_BODY()
		
public:
	// Sets default values for this pawn's properties
	ACBX_Pawn();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OutOfBounds() override;

	void Die();

	void FinishDying();

	FMovementFinished MovementFinished;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCBX_AnimatedStaticMeshComponent* Cube;

protected:
	
	virtual void Move(const FInputActionValue& Value);

	virtual void CheckMovement(FVector2D InputValue);

	virtual void MoveAroundPivot();

	virtual void StopMovement();

	virtual FVector GetPivotPointFromDirection();

	UPROPERTY()
	FVector CubeDimension;

	UPROPERTY()
	FVector LastPosition;

	UPROPERTY()
	int32 CurrentSteps;

	UPROPERTY()
	int32 MaxSteps;

	UPROPERTY()
	FVector2D MovementValue;

	UPROPERTY()
	FTimerHandle MovementTimerHandle;

	UPROPERTY()
	bool InMovement;

	UPROPERTY()
	bool IsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;
};
