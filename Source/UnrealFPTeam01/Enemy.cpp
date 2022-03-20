#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig.h"	
#include "Containers/Array.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RangeEnemy.h"
#include "TowerBase.h"
#include "DrawDebugHelpers.h"

AEnemy::AEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	health = 0.f;
	attackSpeed = 0.f;
	movementSpeed = 0.f;
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();	

	this->GetCharacterMovement()->MaxWalkSpeed = movementSpeed;

	if (this->GetController() && this->GetController()->IsA(AAIController::StaticClass())) {
		aiController = Cast<AAIController>(this->GetController());
		//aiController->RunBehaviorTree();
	}
	

}

void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (aiController && aiController->GetBlackboardComponent()->GetValueAsBool(FName("DetectTowers")) && !isAttacking ) {
		Attack(Cast<ATowerBase>(aiController->GetBlackboardComponent()->GetValueAsObject(FName("DetectedTowers"))));
	}

}


void AEnemy::Attack(ATowerBase* tower) {
	targetTower = tower;
	isAttacking = true;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemy::Reload, 0.1f, true, 1.0f);
}

void AEnemy::Reload() {
	reloadTimer += 0.1f;

	GLog->Log(FString::FromInt(reloadTimer));

	if (reloadTimer > reloadTime) {
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		Attack(targetTower);
		reloadTimer = 0;
	}
}



