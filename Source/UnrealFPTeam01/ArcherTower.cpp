// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherTower.h"

#include "Kismet/KismetMathLibrary.h"


AArcherTower::AArcherTower()
{
	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower's Tower"));
	BaseComponent->SetCollisionProfileName(TEXT("Custom"));
	BaseComponent->SetCollisionObjectType(ECC_GameTraceChannel3);

	RootComponent = BaseComponent;

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeLocation(FVector(0, 0, 100.f));

	//TowerProjectile = ATowerProjectile::StaticClass();
}

void AArcherTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckHit())
	{
		AActor* Target = FindTarget(ActorsHit);
		//GLog->Log(Target->GetName());
		BalistaRotation(Target);
		
	}
}

void AArcherTower::SpawnProjectile(AActor* target)
{
	ATowerProjectile* TTowerProjectile = GetWorld()->SpawnActor<ATowerProjectile>(TowerProjectile, ProjectileOrigin->GetComponentLocation(), MeshComponent->GetComponentRotation());
	TTowerProjectile->Target = target;
	TTowerProjectile->ProjectileMovement->HomingTargetComponent = target->FindComponentByClass<USceneComponent>();
}

void AArcherTower::BalistaRotation(AActor* target)
{
	FRotator RotationToRotate = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target->GetActorLocation());
	MeshComponent->SetRelativeRotation(RotationToRotate);
}
