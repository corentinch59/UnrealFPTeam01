// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealFPTeam01/TowerProjectile.h"
#include "TowerBase.generated.h"

UCLASS()
class UNREALFPTEAM01_API ATowerBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATowerProjectile> projectile;
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

	UPROPERTY(EditAnywhere, Category=TowerStats)
	int towerHealth;

	UPROPERTY(EditAnywhere, Category=TowerStats)
	int towerDamage;

	UPROPERTY(EditAnywhere, Category=TowerStats)
	float rangeRadius;

	UPROPERTY(BlueprintReadWrite)
	TArray<APawn*> enemiesHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
