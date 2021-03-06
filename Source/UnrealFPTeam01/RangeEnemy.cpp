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

	DrawDebugLine(GetWorld(), this->GetActorLocation(), this->GetActorLocation() + this->GetActorForwardVector() * 150, FColor::Green, false, 15, 0, 1);

	FActorSpawnParameters params;

	AActor* ball = GetWorld()->SpawnActor<AUnrealFPTeam01Projectile>(ballClass, this->GetActorLocation() + this->GetActorForwardVector() * ballSpawnRange, FRotator(0, 0, 0));

	ball->SetActorScale3D(ballSize);

	AUnrealFPTeam01Projectile* projectile = Cast<AUnrealFPTeam01Projectile>(ball);

	projectile->targetEnemy = this;

	GLog->Log("attack");

	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(ball->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	UProjectileMovementComponent* moveComp = Cast<UProjectileMovementComponent>(ball->GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	mesh->SetMaterial(0, ballMaterial);
	moveComp->InitialSpeed = ballSpeed;
	moveComp->MaxSpeed = ballSpeed;
	moveComp->ProjectileGravityScale = 0.f;



	moveComp->Velocity = this->GetActorForwardVector() * ballSpeed;

	Super::Attack(tower);
}




