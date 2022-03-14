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

	virtual void Tick(float DeltaSeconds) override;

public:

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile();
};
