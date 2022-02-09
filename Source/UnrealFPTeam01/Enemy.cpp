#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy() {
	PrimaryActorTick.bCanEverTick = false;

	health = 0.f;
	attackSpeed = 0.f;
	movementSpeed = 0.f;

}

void AEnemy::BeginPlay() {
	Super::BeginPlay();	

	this->GetCharacterMovement()->MaxWalkSpeed = movementSpeed;

}



