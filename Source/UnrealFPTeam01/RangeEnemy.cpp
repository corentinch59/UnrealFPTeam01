#include "RangeEnemy.h"
#include "UnrealFPTeam01Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARangeEnemy::ARangeEnemy() {
	PrimaryActorTick.bCanEverTick = true;

}

void ARangeEnemy::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (isAttacking) {
		//this->SetActorRotation(FRotator(0,-90,0), ETeleportType::ResetPhysics);
	}
}

void ARangeEnemy::Shoot() {
	FActorSpawnParameters params;

	AActor* ball = GetWorld()->SpawnActor<AUnrealFPTeam01Projectile>(ballClass, ballSpawnPosition, FRotator(0, 0, 0));

	if(isCannon)
		ball->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));

	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(ball->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	UProjectileMovementComponent* moveComp = Cast<UProjectileMovementComponent>(ball->GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	mesh->SetMaterial(0, ballMaterial);
	moveComp->InitialSpeed = ballSpeed;
	moveComp->MaxSpeed = ballSpeed;
	moveComp->ProjectileGravityScale = 0.f;

	moveComp->Velocity = FVector(ballSpeed, 0, 0);

//	GLog->Log("Shoot");
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ARangeEnemy::Reload, 1.0f, true, 0.0f);
}

void ARangeEnemy::Reload() {
	GLog->Log(FString::FromInt(reloadTimer));
	reloadTimer++;

	if (reloadTimer > reloadTime) {
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		Shoot();
		reloadTimer = 0;
	}
}

