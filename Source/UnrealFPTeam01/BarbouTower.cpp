// Fill out your copyright notice in the Description page of Project Settings.


#include "BarbouTower.h"

ABarbouTower::ABarbouTower()
{
	BarbouBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarbouBody"));
	BarbouBody->SetCollisionProfileName(TEXT("TowerP"));


	RootComponent = BarbouBody;

	BarbouBatte = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarbouBatte"));
	BarbouBatte->AttachToComponent(BarbouBody, FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));
	//BarbouBatte->SetCollisionProfileName(TEXT("TowerP"));

}

void ABarbouTower::BashEnemy(TArray<AActor*> ActorsToHit)
{
	for(int i = 0; i < ActorsToHit.Num(); i++)
	{
		AEnemy* enemy = static_cast<AEnemy*>(ActorsToHit[i]);
		enemy->ApplyDamage(this->TowerState == OnRoad ? this->TowerDamageOnRoad : this->TowerDamageOnSide);
	}
}

void ABarbouTower::FindTargets(TArray<AActor*>& ActorsToHit)
{
	for (int i = 0; i < ActorsHit.Num(); i++)
	{
		ActorsToHit.Add(ActorsHit[i]);
	}
}

void ABarbouTower::FindOneTarget(TArray<AActor*>& ActorsTohit)
{
	ActorsTohit.Add(ActorsHit[0]);
}

void ABarbouTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CheckHit() && isActive)
	{
		if (ActorsToDamage.Num() > 0)
		{
			RotateTowardTarget(ActorsToDamage[0]);

			this->TowerState == OnRoad ? this->FindOneTarget(ActorsToDamage) : this->FindTargets(ActorsToDamage);
			BashEnemy(ActorsToDamage);
		}
	}
}

void ABarbouTower::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < BarbouBody->GetNumMaterials(); i++)
	{
		BarbouMaterials.Add(BarbouBody->GetMaterial(i));
	}

	for (int i = 0; i < BarbouBatte->GetNumMaterials(); i++)
	{
		BarbouMaterials.Add(BarbouBatte->GetMaterial(i));
	}

	BarbouBody->OnClicked.AddDynamic(this, &ABarbouTower::OnClicked);
	BarbouBatte->OnClicked.AddDynamic(this, &ABarbouTower::OnClicked);

}

void ABarbouTower::SetGreenPlacement()
{
	Super::SetGreenPlacement();

	for (int i = 0; i < BarbouBody->GetNumMaterials(); i++)
	{
		BarbouBody->SetMaterial(i, GreenMaterial);
	}

	for (int i = 0; i < BarbouBatte->GetNumMaterials(); i++)
	{
		BarbouBatte->SetMaterial(i, GreenMaterial);
	}
}

void ABarbouTower::SetBluePlacement()
{
	Super::SetBluePlacement();

	for (int i = 0; i < BarbouBody->GetNumMaterials(); i++)
	{
		BarbouBody->SetMaterial(i, BlueMaterial);
	}

	for (int i = 0; i < BarbouBatte->GetNumMaterials(); i++)
	{
		BarbouBatte->SetMaterial(i, BlueMaterial);
	}
}

void ABarbouTower::SetMeshMaterials()
{
	Super::SetMeshMaterials();

	for (int i = 0; i < BarbouBody->GetNumMaterials(); i++)
	{
		BarbouBody->SetMaterial(i, BarbouMaterials[i]);
	}

	for (int i = 0; i < BarbouBatte->GetNumMaterials(); i++)
	{
		BarbouBatte->SetMaterial(i, BarbouMaterials[i]);
	}
}

void ABarbouTower::InitializeTower()
{
	Super::InitializeTower();

	if (!isActive)
	{
		BarbouBody->SetCollisionProfileName(TEXT("NoCollisionC"));
		BarbouBatte->SetCollisionProfileName(TEXT("NoCollisionC"));
		this->SetActorScale3D(FVector(.25f, .25f, .25f));
	}
}

void ABarbouTower::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);
}


