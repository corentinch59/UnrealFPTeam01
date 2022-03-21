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

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void SetGreenPlacement() override;

	virtual void SetBluePlacement() override;

	virtual void SetMeshMaterials() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATowerProjectile> TowerProjectile;

	UPROPERTY(VisibleAnywhere)
		TArray<UMaterialInterface*> AdditionalMeshMaterials;

	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;

	UFUNCTION(BlueprintCallable)
		void SpawnProjectile(AActor* target);

	UFUNCTION(BlueprintCallable)
		void BalistaRotation(AActor* target);

};
