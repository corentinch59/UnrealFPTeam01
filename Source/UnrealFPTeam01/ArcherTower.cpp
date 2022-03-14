// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherTower.h"


void AArcherTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckHit())
	{
		AActor* Target = FindTarget(ActorsHit);
		//GLog->Log(Target->GetName());
	}
}

void AArcherTower::SpawnProjectile()
{
	ATowerProjectile* TTowerProjectile = GetWorld()->SpawnActor<ATowerProjectile>(TowerProjectile, ProjectileOrigin->GetComponentLocation(), MeshComponent->GetComponentRotation());
}
