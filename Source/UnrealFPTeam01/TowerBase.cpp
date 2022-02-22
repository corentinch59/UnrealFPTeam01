// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = MeshComponent;

	ProjectileOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileOrigin"));
	ProjectileOrigin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TowerHealth = 100;
	TowerDamage = 1;
	TowerRangeRadius = 250.f;
	TowerAttackRate = 1.f;

}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagOfEndPath, EndPathActors);
	if(EndPathActors.Num() > 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Too many End Paths ! %f"), GetWorld()->TimeSeconds));
	}

}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATowerBase::CheckHit()
{
	FVector sphereOrigin = this->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objectsTypeToQuerry;
	objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	bool bHasHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereOrigin, TowerRangeRadius, objectsTypeToQuerry, nullptr, actorsToIgnore, ActorsHit);

	DrawDebugSphere(GetWorld(), sphereOrigin, TowerRangeRadius, 40, FColor(255, 0, 0));

	return bHasHit;
}

void ATowerBase::TowerTakeDamage(int damage)
{
	TowerHealth -= damage;
}

void ATowerBase::DestroyTower()
{
	Destroy();
}

void ATowerBase::SpawnProjectile()
{
	ATowerProjectile* TTowerProjectile = GetWorld()->SpawnActor<ATowerProjectile>(TowerProjectile, ProjectileOrigin->GetComponentLocation(), MeshComponent->GetComponentRotation());
}

// Called to bind functionality to input
void ATowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

