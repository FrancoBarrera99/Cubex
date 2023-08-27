// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Grid/CBX_GridCell.h"

UCBX_GridCell::UCBX_GridCell()
{
	VisibilityAnimationRate = 0.0166f;
	SetVisibility(false);
	bIsUpdating = false;
	VisibilityAnimationState = Waiting;
}

void UCBX_GridCell::BeginPlay()
{
	Super::BeginPlay();
}

void UCBX_GridCell::SetState(const ECellState& NewCellState)
{
	CellState = NewCellState;
}

ECellState UCBX_GridCell::GetState()
{
	return CellState;
}

void UCBX_GridCell::SetIndex(const int32& NewIndex)
{
	Index = NewIndex;
}

int32 UCBX_GridCell::GetIndex()
{
	return Index;
}

void UCBX_GridCell::ChangeVisibility(bool bIsVisible)
{
	if (IsVisible() == bIsVisible || VisibilityAnimationState != Waiting)
	{
		return;
	}
	
	if (bIsVisible)
	{
		VisibilityAnimationState = Showing;
		SetVisibility(true);
	}else
	{
		VisibilityAnimationState = Hiding;
	}
	GetWorld()->GetTimerManager().SetTimer(VisibilityAnimationTimerHandle, this, &UCBX_GridCell::UpdateScale, VisibilityAnimationRate, true);
}

void UCBX_GridCell::UpdateScale()
{
	if (VisibilityAnimationState == Finished)
	{
		StopUpdatingScale();
		return;
	}

	FVector NewScale = GetRelativeScale3D();
	VisibilityAnimationState == Showing ? NewScale += FVector(VisibilityAnimationRate) : NewScale -= FVector(VisibilityAnimationRate);

	// Clamp the values to ensure they are between 0.1 and 1
	NewScale.X = FMath::Clamp(static_cast<float>(NewScale.X), 0.05f, 1.0f);
	NewScale.Y = FMath::Clamp(static_cast<float>(NewScale.Y), 0.05f, 1.0f);
	NewScale.Z = FMath::Clamp(static_cast<float>(NewScale.Z), 0.05f, 1.0f);
	
	SetRelativeScale3D(NewScale);

	if (ShouldFinishAnimation())
	{
		if (VisibilityAnimationState == Hiding)
		{
			SetVisibility(false);
		}
		VisibilityAnimationState = Finished;
	}
}

void UCBX_GridCell::StopUpdatingScale()
{
	if (VisibilityAnimationTimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(VisibilityAnimationTimerHandle);
	VisibilityAnimationState = Waiting;
}

bool UCBX_GridCell::ShouldFinishAnimation() const
{
	constexpr float Tolerance = 0.001f;
	if ((FVector::Dist(GetRelativeScale3D(), FVector(1.0f)) < Tolerance) && VisibilityAnimationState == Showing)
	{
		return true;
	}

	if ((FVector::Dist(GetRelativeScale3D(), FVector(0.05f)) < Tolerance) && VisibilityAnimationState == Hiding)
	{
		return true;
	}
	
	return false;
}
