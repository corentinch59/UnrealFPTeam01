// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherTower.h"

#include "Kismet/KismetMathLibrary.h"


AArcherTower::AArcherTower()
{
	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower's Tower"));
	BaseComponent->SetCollisionProfileName(TEXT("TowerP"));

	RootComponent = BaseComponent;

	MeshComponent->SetCollisionProfileName(TEXT("TowerP"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeLocation(FVector(0, 0, 100.f));

	ProjectileOrigin->SetRelativeLocation(FVector(26.f, 0.f, 47.f));

	//TowerProjectile = ATowerProjectile::StaticClass();

	AttackCooldown = 0.f;
}

void AArcherTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckHit() && isActive)
	{
		AActor* Target = FindTarget(ActorsHit);
		//GLog->Log(Target->GetName());
		BalistaRotation(Target);
		if(AttackCooldown <= 0.f)
		{
			SpawnProjectile(Target);
			AttackCooldown = 1 / TowerAttackRate;
		}
	}
	AttackCooldown -= GetWorld()->DeltaTimeSeconds;



}

void AArcherTower::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < BaseComponent->GetNumMaterials(); i++)
	{
		AdditionalMeshMaterials.Add(BaseComponent->GetMaterial(i));
	}

	BaseComponent->OnClicked.AddDynamic(this, &ATowerBase::OnClicked);

	/*GLog->Log("Number of Additional materials : " + FString::FromInt(AdditionalMeshMaterials.Num()));
	GLog->Log(AdditionalMeshMaterials[0]->GetName());*/

}

void AArcherTower::SpawnProjectile(AActor* target)
{
	FTransform SpawnLocation = {MeshComponent->GetRelativeRotation(), ProjectileOrigin->GetComponentLocation(), FVector(1.f,1.f,1.f) };

	ATowerProjectile* TTowerProjectile = GetWorld()->SpawnActorDeferred<ATowerProjectile>(TowerProjectile, SpawnLocation);

	TTowerProjectile->InitializeProjectile(target);
	TTowerProjectile->FinishSpawning(SpawnLocation);

}

void AArcherTower::BalistaRotation(AActor* target)
{
	FRotator RotationToRotate = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target->GetActorLocation());
	FRotator newRotation = { 0.f, RotationToRotate.Yaw, 0.f };
	MeshComponent->SetRelativeRotation(newRotation);
}

void AArcherTower::SetGreenPlacement()
{
	Super::SetGreenPlacement();

	for (int i = 0; i < BaseComponent->GetNumMaterials(); i++)
	{
		BaseComponent->SetMaterial(i, GreenMaterial);
	}
}

void AArcherTower::SetBluePlacement()
{
	Super::SetBluePlacement();

	for (int i = 0; i < BaseComponent->GetNumMaterials(); i++)
	{
		BaseComponent->SetMaterial(i, BlueMaterial);
	}
}

void AArcherTower::SetMeshMaterials()
{
	Super::SetMeshMaterials();

	for (int i = 0; i < AdditionalMeshMaterials.Num(); i++)
	{
		BaseComponent->SetMaterial(i, AdditionalMeshMaterials[i]);
	}
}

