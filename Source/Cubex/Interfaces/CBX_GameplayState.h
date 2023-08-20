// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBX_GameplayState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCBX_GameplayState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CUBEX_API ICBX_GameplayState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Start() = 0;
	virtual void NextState() = 0;
	virtual void Stop() = 0;
	virtual int32 GetLevel() = 0;
};
