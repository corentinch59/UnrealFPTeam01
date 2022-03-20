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

	FVector WantedDir = (Target->GetActorLocation() - GetActorLocation());
	WantedDir += Target->GetVelocity() * WantedDir.Size() / ProjectileSpeed;
	ProjectileMovement->Velocity += WantedDir * ProjectileSpeed * GetWorld()->DeltaTimeSeconds;
	ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * ProjectileSpeed;
}

void ATowerProjectile::InitializeProjectile(AActor* targetToSet)
{
	Target = targetToSet;
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

