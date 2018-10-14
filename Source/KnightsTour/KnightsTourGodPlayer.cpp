// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightsTourGodPlayer.h"

#include "Camera/CameraComponent.h"

#include "Components/SphereComponent.h"

#include "GameFramework/SpringArmComponent.h"



// Sets default values
AKnightsTourGodPlayer::AKnightsTourGodPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AKnightsTourGodPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnightsTourGodPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKnightsTourGodPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AKnightsTourGodPlayer::MoveForward(float Value)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Value);
}

void AKnightsTourGodPlayer::MoveRight(float Value)
{
	SetActorLocation(GetActorLocation() + GetActorRightVector() * Value);
}

void AKnightsTourGodPlayer::AddYaw(float Value)
{
	SetActorRotation(GetActorRotation() + FQuat(GetActorUpVector(), FMath::DegreesToRadians(Value)).Rotator());
}


void AKnightsTourGodPlayer::SetupComponents()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CreateCollisionComponent();
	CreateSpringArmComponent();
	CreateCameraComponent();
}

void AKnightsTourGodPlayer::CreateCollisionComponent()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->InitSphereRadius(40.0f); //TODO: Remove Hard Coding & 
	CollisionComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->BodyInstance.SetResponseToAllChannels(ECR_Block);
	CollisionComponent->BodyInstance.SetResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AKnightsTourGodPlayer::CreateSpringArmComponent()
{
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	//OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArmComponent->TargetArmLength = 400.f; //TODO: Remove Hard Coding & 
	CameraSpringArmComponent->SetRelativeRotation(FQuat(FVector(0.0f, 1.0f, 0.0f), FMath::DegreesToRadians(45.0f))); //TODO: Is y-axis defined somewhere
	CameraSpringArmComponent->bEnableCameraLag = true;
	CameraSpringArmComponent->CameraLagSpeed = 3.0f;
}

void AKnightsTourGodPlayer::CreateCameraComponent()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
}

