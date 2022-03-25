// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "BarbouTower.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPTEAM01_API ABarbouTower : public ATowerBase
{
	GENERATED_BODY()

public:

	ABarbouTower();

	UPROPERTY(VisibleAnywhere, Category=BarbouSetups)
	USkeletalMeshComponent* BarbouBody;

	UPROPERTY(VisibleAnywhere, Category = BarbouSetups)
	USkeletalMeshComponent* BarbouBatte;

	UPROPERTY(VisibleDefaultsOnly)
	TArray<AActor*> ActorsToDamage;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMaterialInterface*> BarbouMaterials;

	UFUNCTION(BlueprintCallable)
	void BashEnemy(TArray<AActor*> ActorsToHit);

	UFUNCTION(BlueprintCallable)
	void FindTargets(TArray<AActor*>& ActorsToHit);

	UFUNCTION(BlueprintCallable)
	void FindOneTarget(TArray<AActor*>& ActorsToHit);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void SetGreenPlacement() override;

	virtual void SetBluePlacement() override;

	virtual void SetMeshMaterials() override;

	virtual void InitializeTower() override;

	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) override;
};
