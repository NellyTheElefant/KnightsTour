// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightsTourGodPlayerController.h"

#include "KnightsTourGodPlayer.h"

AKnightsTourGodPlayerController::AKnightsTourGodPlayerController() :
	APlayerController(),
	bIsMovementDisabled(false),
	PossessedPawn(nullptr),
	MinSpeed(5.0f), //TODO: Remove hardcoded default values
	MaxSpeed(20.0f)
{
	bShowMouseCursor = true;
}

void AKnightsTourGodPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();
	
	SetupAxisBindings();
	SetupActionBindings();
}

void AKnightsTourGodPlayerController::Possess(APawn * PawnToPossess)
{
	APlayerController::Possess(PawnToPossess);
	InitialisePossesedPawn(PawnToPossess);
}

void AKnightsTourGodPlayerController::SetupAxisBindings()
{
	InputComponent->BindAxis("MoveForward", this, &AKnightsTourGodPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AKnightsTourGodPlayerController::MoveRight);
	InputComponent->BindAxis("RotateClockwise", this, &AKnightsTourGodPlayerController::RotateClockwise);
}

void AKnightsTourGodPlayerController::SetupActionBindings()
{

}

void AKnightsTourGodPlayerController::InitialisePossesedPawn(APawn * PawnToPossess)
{
	PossessedPawn = Cast<AKnightsTourGodPlayer>(PawnToPossess);
	if (!PossessedPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("KnightsTourGodPlayerController::InitialisePossesedPawn() failed to initialise PossessedPawn"));
	}
}

float AKnightsTourGodPlayerController::CalculateMovementSpeed()
{
	//TODO: Implement this (Make a function of spring arm length). Clamp between min and max speed
	return 10.0f;
}

float AKnightsTourGodPlayerController::CalculateRotationSpeed()
{
	//TODO: Implement this (Make a function of spring arm length?)
	return 5.0f;
}

bool AKnightsTourGodPlayerController::CanMove(float AxisValue)
{
	return !FMath::IsNearlyZero(AxisValue) && PossessedPawn && !bIsMovementDisabled;
}

void AKnightsTourGodPlayerController::MoveForward(float Value)
{
	if (CanMove(Value))
	{
		PossessedPawn->MoveForward(Value * CalculateMovementSpeed());
	}
}

void AKnightsTourGodPlayerController::MoveRight(float Value)
{
	if (CanMove(Value))
	{
		PossessedPawn->MoveRight(Value * CalculateMovementSpeed()); //TODO: Consider caching movement speed
	}
}

void AKnightsTourGodPlayerController::RotateClockwise(float Value)
{
	if (CanMove(Value))
	{
		PossessedPawn->AddYaw(Value * CalculateRotationSpeed()); 
	}
}
