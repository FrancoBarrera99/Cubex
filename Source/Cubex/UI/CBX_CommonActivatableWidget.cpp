// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubex/UI/CBX_CommonActivatableWidget.h"

UCBX_CommonActivatableWidget::UCBX_CommonActivatableWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TOptional<FUIInputConfig> UCBX_CommonActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case ELyraWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case ELyraWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case ELyraWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case ELyraWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}
