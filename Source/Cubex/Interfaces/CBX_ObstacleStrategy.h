// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cubex/Gameplay/CBX_GridManager.h"
#include "UObject/Interface.h"
#include "CBX_ObstacleStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBX_ObstacleStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CUBEX_API ICBX_ObstacleStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void BuildObstacle(ACBX_GridManager* GridManager) = 0;
	
};
