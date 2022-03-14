#include "Cannon.h"
#include "UnrealFPTeam01Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACannon::ACannon() {
	PrimaryActorTick.bCanEverTick = true;

}

void ACannon::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (isAttacking) {
		this->SetActorRotation(FRotator(0,-90,0), ETeleportType::ResetPhysics);
	}
}

void ACannon::Shoot() {
	FActorSpawnParameters params;

	AActor* ball = GetWorld()->SpawnActor<AUnrealFPTeam01Projectile>(ballClass, ballSpawnPosition, FRotator(0, 0, 0));
	ball->SetActorScale3D(FVector(1.5f, 1.5f,1.5f));
	UProjectileMovementComponent* moveComp = Cast<UProjectileMovementComponent>(ball->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
	moveComp->InitialSpeed = ballSpeed;
	moveComp->MaxSpeed = ballSpeed;
	moveComp->ProjectileGravityScale = 0.f;

	moveComp->Velocity = FVector(ballSpeed,0,0);

	GetWorld()->GetTimerManager().SetTimer(timerHandle,this,&ACannon::Reload,1.0f,true,0.0f);
}

void ACannon::Reload() {
	GLog->Log(FString::FromInt(reloadTimer));
	reloadTimer++;

	if (reloadTimer > reloadTime) {
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		Shoot();
		reloadTimer = 0;
	}
}