// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "ArcherTower.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPTEAM01_API AArcherTower : public ATowerBase
{
	GENERATED_BODY()

public:

	AArcherTower();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseComponent;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATowerProjectile> TowerProjectile;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(AActor* target);

	UFUNCTION(BlueprintCallable)
	void BalistaRotation(AActor* target);

};
