// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Player/CBX_Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACBX_Pawn::ACBX_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CubeDimension = FVector(50.0f);
	LastPosition = FVector(0.0f);
	CurrentSteps = 0;
	MaxSteps = 8;
	MovementValue = FVector2D(0);
	InMovement = false;

}

// Called to bind functionality to input
void ACBX_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ACBX_Pawn::Move);
	}
}

void ACBX_Pawn::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (FMath::Abs(MoveValue.X) >= FMath::Abs(MoveValue.Y))
	{
		CheckMovement(FVector2D(MoveValue.X, 0));
	}else
	{
		CheckMovement(FVector2D(0, -(MoveValue.Y)));
	}
}

void ACBX_Pawn::CheckMovement(FVector2D InputValue)
{
	if (!InMovement)
	{
		InMovement = true;
		MovementValue = InputValue;
		LastPosition = GetActorLocation();

		GetWorldTimerManager().SetTimer(MovementTimerHandle, this, &ACBX_Pawn::MoveAroundPivot, 0.0166f, true);
	}
}

void ACBX_Pawn::MoveAroundPivot()
{
	if (CurrentSteps < MaxSteps)
	{
		const float AngleDegree = (1.0f / MaxSteps) * 90.0f;
		const FVector InputAxis = FVector(-(MovementValue.Y), MovementValue.X, 0.0f); 

		FVector InVector = GetActorLocation() - GetPivotPointFromDirection();
		FVector RotatedVector = InVector.RotateAngleAxis(AngleDegree , InputAxis.GetSafeNormal());
		FVector NewPosition = RotatedVector + GetPivotPointFromDirection();

		FRotator InRotator = UKismetMathLibrary::RotatorFromAxisAndAngle(InputAxis, AngleDegree);
		FRotator NewRotation = UKismetMathLibrary::ComposeRotators(GetActorRotation(), InRotator);

		SetActorLocationAndRotation(NewPosition, NewRotation);

		CurrentSteps++;
	}else
	{
		CurrentSteps = 0;
		GetWorldTimerManager().ClearTimer(MovementTimerHandle);
		InMovement = false;
	}
}

FVector ACBX_Pawn::GetPivotPointFromDirection()
{
	FVector PivotPoint = FVector(0.0f);

	const float MovementOnX = LastPosition.X + MovementValue.X * CubeDimension.X;
	const float MovementOnY = LastPosition.Y + MovementValue.Y * CubeDimension.Y;
	const float MovementOnZ = LastPosition.Z - CubeDimension.Z;
	
	PivotPoint = FVector(MovementOnX, MovementOnY, MovementOnZ);
	DrawDebugSphere(GetWorld(), PivotPoint, 15.0f, 12, FColor::Red, false, 1.0f, 0, 3.0f);
	
	return PivotPoint;
}
