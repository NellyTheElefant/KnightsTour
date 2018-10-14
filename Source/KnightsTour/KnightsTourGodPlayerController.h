// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KnightsTourGodPlayerController.generated.h"

/**
 * 
 */

class AKnightsTourGodPlayer;

UCLASS()
class KNIGHTSTOUR_API AKnightsTourGodPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKnightsTourGodPlayerController();

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	virtual void Possess(APawn* PawnToPossess) override;

protected:
	bool bIsMovementDisabled;
	
	AKnightsTourGodPlayer* PossessedPawn;

	float MinSpeed;
	float MaxSpeed;

	// Axis Bindings
	void SetupAxisBindings();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateClockwise(float Value);

	// Action Bindings
	void SetupActionBindings();

private:
	void InitialisePossesedPawn(APawn* PawnToPossess);
	
	// Movement
	bool  CanMove(float AxisValue);
	float CalculateMovementSpeed();
	float CalculateRotationSpeed();
	
};
