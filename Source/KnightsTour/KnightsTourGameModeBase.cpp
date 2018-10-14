// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightsTourGameModeBase.h"

#include "KnightsTourGodPlayer.h"
#include "KnightsTourGodPlayerController.h"

AKnightsTourGameModeBase::AKnightsTourGameModeBase() :
	AGameModeBase()
{
	PlayerControllerClass = AKnightsTourGodPlayerController::StaticClass();
	DefaultPawnClass = AKnightsTourGodPlayer::StaticClass();
}