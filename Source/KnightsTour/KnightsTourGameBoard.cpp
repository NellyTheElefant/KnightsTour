// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightsTourGameBoard.h"

#include "KnightsTourBoardTile.h"


#include "Engine/World.h"

#include "Materials/Material.h"

#include "ConstructorHelpers.h"


// Sets default values
AKnightsTourGameBoard::AKnightsTourGameBoard() :
	Tiles(),
	TileSize(0),
	NumColumns(GameBoardUtility::DEFAULT_COL_SIZE), 
	NumRows(GameBoardUtility::DEFAULT_ROW_SIZE)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CacheMaterials();
}

void AKnightsTourGameBoard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ConstructSquareBoard(Transform);
}

// Called when the game starts or when spawned
void AKnightsTourGameBoard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKnightsTourGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnightsTourGameBoard::CacheMaterials()
{
	CacheTileMaterials();
}

void AKnightsTourGameBoard::CacheTileMaterials()
{
	ConstructorHelpers::FObjectFinder<UMaterial> DarkMaterial(TEXT("Material'/Game/Materials/M_Basic_Dark.M_Basic_Dark'"));
	TileMaterialMap.Emplace(GameBoardUtility::TILE_STATE::IDLE_DARK, DarkMaterial.Object);

	ConstructorHelpers::FObjectFinder<UMaterial> LightMaterial(TEXT("Material'/Game/Materials/M_Basic_Light.M_Basic_Light'"));
	TileMaterialMap.Emplace(GameBoardUtility::TILE_STATE::IDLE_LIGHT, LightMaterial.Object);
}

void AKnightsTourGameBoard::ConstructSquareBoard(const FTransform& Transform)
{
	if (GetWorld() && Tiles.Num() == 0)
	{
		for (unsigned int Row = 0; Row < NumRows; ++Row)
		{
			for (unsigned int Col = 0; Col < NumColumns; ++Col)
			{
				AddTile(Row, Col, Transform);
			}
		}
	}
}

void AKnightsTourGameBoard::AddTile(unsigned int Row, unsigned int Col, const FTransform & Transform)
{
	FTransform Translation(CoordinatesToVector(Row, Col));
	FTransform SpawnTransform = Transform + Translation;
	AKnightsTourBoardTile* Tile = GetWorld()->SpawnActor<AKnightsTourBoardTile>(SpawnTransform.GetTranslation(), SpawnTransform.GetRotation().Rotator());
	Tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	Tile->SetMaterial(CoordinatesToMaterial(Row, Col));
	Tiles.Add(Tile);
}

void AKnightsTourGameBoard::DestroyBoard()
{
	for (AKnightsTourBoardTile* Tile : Tiles)
	{
		if (Tile)
		{
			Tile->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			Tile->Destroy();
		}
	}
	Tiles.Empty();
}

bool AKnightsTourGameBoard::IsValidRow(unsigned int Row)
{
	return Row < NumRows;
}

bool AKnightsTourGameBoard::IsValidCol(unsigned int Col)
{
	return Col < NumColumns;
}

FVector AKnightsTourGameBoard::CoordinatesToVector(unsigned int Row, unsigned int Col)
{
	return FVector(static_cast<float>(Row) * GameBoardUtility::DEFAULT_TILE_SIZE, static_cast<float>(Col) * GameBoardUtility::DEFAULT_TILE_SIZE, 0.0f);
}

TTuple<int, int> AKnightsTourGameBoard::VectorToCoordinates(FVector Location)
{
	return TTuple<int, int>();
}

GameBoardUtility::TILE_COLOUR AKnightsTourGameBoard::CoordinatesToTileColour(unsigned int Row, unsigned int Col)
{
	using namespace SimpleMath;

	if (!IsValidRow(Row) || !IsValidCol(Col))
	{
		return GameBoardUtility::TILE_COLOUR::INVALID_COLOUR;
	}

	if ((IsEven(Row) && IsOdd(Col)) || (IsOdd(Row) && IsEven(Col)))
	{
		return GameBoardUtility::TILE_COLOUR::DARK;
	}
	else
	{
		return GameBoardUtility::TILE_COLOUR::LIGHT;
	}
}

UMaterial* AKnightsTourGameBoard::TileColourToMaterial(GameBoardUtility::TILE_COLOUR Colour)
{
	switch (Colour)
	{
	case GameBoardUtility::TILE_COLOUR::DARK:
	{
		return TileMaterialMap[GameBoardUtility::TILE_STATE::IDLE_DARK];
	}
	case GameBoardUtility::TILE_COLOUR::LIGHT:
	{
		return TileMaterialMap[GameBoardUtility::TILE_STATE::IDLE_LIGHT];
	}
	case GameBoardUtility::TILE_COLOUR::INVALID_COLOUR:
	default:
	{
		return nullptr;
	}
	}
}

UMaterial* AKnightsTourGameBoard::CoordinatesToMaterial(unsigned int Row, unsigned int Col)
{
	if (!IsValidRow(Row) || !IsValidCol(Col))
	{
		return nullptr;
	}
	GameBoardUtility::TILE_COLOUR Colour = CoordinatesToTileColour(Row, Col);
	return TileColourToMaterial(Colour);
}
