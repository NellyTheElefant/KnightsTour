// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KnightsTourBoardTile.generated.h"

class UStaticMeshComponent;
class UMaterial;

UCLASS()
class KNIGHTSTOUR_API AKnightsTourBoardTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKnightsTourBoardTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TileComponent;

	UPROPERTY(EditAnywhere)
	UMaterial*			  TileMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetMaterial(UMaterial* Material);

private:
	// Components
	void SetupComponents();
	void CreateStaticMeshComponent();
	void CreateMaterialComponent();
	
	
};
