// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBox.generated.h"

UENUM()
enum BoxType
{
	TArcherTower	UMETA(DisplayName = "Archer Tower"),
	TKnightTower	UMETA(DisplayName = "Knight Tower"),
	TBarbouTower	UMETA(DisplayName = "Barbou Tower"),
	TNobertTower	UMETA(DisplayName = "Norbert Tower"),
	TRambouTower	UMETA(DisplayName = "Rambou Tower")
};

UCLASS()
class UNREALFPTEAM01_API ATowerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBox();

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<BoxType> BoxType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
