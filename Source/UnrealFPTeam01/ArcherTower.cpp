// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherTower.h"


void AArcherTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckHit();
}
