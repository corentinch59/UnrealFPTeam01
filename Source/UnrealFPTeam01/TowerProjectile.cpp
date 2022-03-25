// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerProjectile.h"

// Sets default values
ATowerProjectile::ATowerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetEnableGravity(false);
	RootComponent = MeshComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;

	AngleOffset = 0.f;
	SpawnTime = 0.f;
}

// Called when the game starts or when spawned
void ATowerProjectile::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &ATowerProjectile::OnHit);

	//GLog->Log(Target->GetName());

}

// Called every frame
void ATowerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(lifeTime <= 0.f)
	{
		Destroy();
	}
	lifeTime -= GetWorld()->DeltaTimeSeconds;

	if(SpawnTime >= 0.f)
	{
		FVector targetDir = (Target->GetActorLocation() - GetActorLocation());
		float angle = FMath::Atan2(targetDir.GetSafeNormal().Y, targetDir.GetSafeNormal().X);

		FVector NewDir = { FMath::Cos(angle + AngleOffset), FMath::Sin(angle + AngleOffset), 0.f };

		ProjectileMovement->Velocity += NewDir * ProjectileSpeed * GetWorld()->DeltaTimeSeconds;
		ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * ProjectileSpeed;

	}
	else
	{
		FVector WantedDir = (Target->GetActorLocation() - GetActorLocation());
		WantedDir += Target->GetVelocity() * WantedDir.Size() / ProjectileSpeed;
		ProjectileMovement->Velocity += WantedDir * ProjectileSpeed * GetWorld()->DeltaTimeSeconds;
		ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * ProjectileSpeed;
	}
	SpawnTime -= GetWorld()->DeltaTimeSeconds;
}

void ATowerProjectile::InitializeProjectile(AActor* targetToSet, float timeUntil, float offset)
{
	Target = targetToSet;
	AngleOffset = offset;
	SpawnTime = timeUntil;
}

void ATowerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if(Pawn ==  nullptr)
	{
		return;
	}

	Destroy();
}

