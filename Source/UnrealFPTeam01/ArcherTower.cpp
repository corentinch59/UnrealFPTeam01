// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherTower.h"


AArcherTower::AArcherTower()
{
	TowersTower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower's Tower"));
	TowersTower->SetCollisionProfileName(TEXT("Custom"));
	TowersTower->SetCollisionObjectType(ECC_GameTraceChannel3);

	RootComponent = TowersTower;

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeLocation(FVector(0, 0, 100.f));
}

void AArcherTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckHit())
	{
		AActor* Target = FindTarget(ActorsHit);
		//GLog->Log(Target->GetName());
		RotateTowardTarget(Target);
	}
}

void AArcherTower::SpawnProjectile(AActor* target)
{
	ATowerProjectile* TTowerProjectile = GetWorld()->SpawnActor<ATowerProjectile>(TowerProjectile, ProjectileOrigin->GetComponentLocation(), MeshComponent->GetComponentRotation());
}
