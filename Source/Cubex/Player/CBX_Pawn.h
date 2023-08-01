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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Move(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;
};
