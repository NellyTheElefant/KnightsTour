// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightsTourBoardTile.h"

#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

#include "Materials/Material.h"

// Sets default values
AKnightsTourBoardTile::AKnightsTourBoardTile() :
	TileComponent(nullptr),
	TileMaterial(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}


// Called when the game starts or when spawned
void AKnightsTourBoardTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnightsTourBoardTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKnightsTourBoardTile::SetMaterial(UMaterial* Material)
{
	if (Material)
	{
		TileMaterial = Material;
		TileComponent->SetMaterial(0, TileMaterial);
	}
}


void AKnightsTourBoardTile::SetupComponents()
{
	CreateStaticMeshComponent();
	CreateMaterialComponent();
	RootComponent = TileComponent;
}

void AKnightsTourBoardTile::CreateStaticMeshComponent()
{
	TileComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Meshes/Floor_400x400.Floor_400x400'"));
	if (StaticMesh.Object)
	{
		TileComponent->SetStaticMesh(StaticMesh.Object);
	}

}

void AKnightsTourBoardTile::CreateMaterialComponent()
{
	TileMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
}
