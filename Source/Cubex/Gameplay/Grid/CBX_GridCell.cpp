// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/Gameplay/Grid/CBX_GridCell.h"

UCBX_GridCell::UCBX_GridCell()
{
	
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
