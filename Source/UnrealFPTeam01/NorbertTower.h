// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "NorbertTower.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPTEAM01_API ANorbertTower : public ATowerBase
{
	GENERATED_BODY()

public:

	ANorbertTower();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void InitializeTower() override;

};
