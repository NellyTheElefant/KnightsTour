// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "KnightsTourGameBoardUtility.h"

#include "KnightsTourGameBoard.generated.h"



class UStaticMeshComponent;
class AKnightsTourBoardTile;

UCLASS()
class KNIGHTSTOUR_API AKnightsTourGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKnightsTourGameBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	TArray<AKnightsTourBoardTile*> Tiles;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	unsigned int NumColumns;

	UPROPERTY(EditDefaultsOnly)
	unsigned int NumRows;

private:
	// Initialisation
	void CacheMaterials();
	void CacheTileMaterials();
	void ConstructSquareBoard(const FTransform& Transform);

	void AddTile(unsigned int Row, unsigned int Col, const FTransform & Transform);

	int TileSize;

	void DestroyBoard();

	bool IsValidRow(unsigned int Row);
	bool IsValidCol(unsigned int Col);

	FVector			  CoordinatesToVector(unsigned int Row, unsigned int Col); 
	TTuple<int, int>  VectorToCoordinates(FVector Location);

	GameBoardUtility::TILE_COLOUR CoordinatesToTileColour(unsigned int Row, unsigned int Col);
	UMaterial*					  TileColourToMaterial(GameBoardUtility::TILE_COLOUR Colour);
	UMaterial*					  CoordinatesToMaterial(unsigned int Row, unsigned int Col);

	TMap<GameBoardUtility::TILE_STATE, UMaterial*>	TileMaterialMap;

};
