// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KnightsTourGodPlayer.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class KNIGHTSTOUR_API AKnightsTourGodPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKnightsTourGodPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void AddYaw(float Value);

private:
	// Components
	void SetupComponents();
	void CreateCollisionComponent();
	void CreateSpringArmComponent();
	void CreateCameraComponent();
	
};
