// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "CBX_Pawn.generated.h"

class UInputAction;

UCLASS()
class CUBEX_API ACBX_Pawn : public APawn
{
	GENERATED_BODY()
		
public:
	// Sets default values for this pawn's properties
	ACBX_Pawn();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;

protected:
	
	virtual void Move(const FInputActionValue& Value);

	virtual void CheckMovement(FVector2D InputValue);

	virtual void MoveAroundPivot();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;
};
