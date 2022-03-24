#include "RangeEnemy.h"
#include "UnrealFPTeam01Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "DrawDebugHelpers.h"

ARangeEnemy::ARangeEnemy() {
	PrimaryActorTick.bCanEverTick = true;

}

void ARangeEnemy::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}

void ARangeEnemy::Attack(ATowerBase* tower) {
	targetTower = tower;
	isAttacking = true;

	ballSpawnPosition = (this->GetActorLocation() + offsetBallSpawn) + this->GetActorForwardVector() * -1 * 100;

	DrawDebugLine(GetWorld(), this->GetActorLocation(), ballSpawnPosition, FColor::Green, false, 15, 0, 1);

	FActorSpawnParameters params;

	AActor* ball = GetWorld()->SpawnActor<AUnrealFPTeam01Projectile>(ballClass, ballSpawnPosition, FRotator(0, 0, 0));

	if (isCannon)
		ball->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));

	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(ball->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	UProjectileMovementComponent* moveComp = Cast<UProjectileMovementComponent>(ball->GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	mesh->SetMaterial(0, ballMaterial);
	moveComp->InitialSpeed = ballSpeed;
	moveComp->MaxSpeed = ballSpeed;
	moveComp->ProjectileGravityScale = 0.f;

	moveComp->Velocity = FVector(0, -ballSpeed, 0);

	Super::Attack(tower);
}




