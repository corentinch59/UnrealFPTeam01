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
	GLog->Log("begin played enemy");

	//this->AIControllerClass = AAIController::StaticClass();

	if (this->GetController() && this->GetController()->IsA(AAIController::StaticClass())) {
		aiController = Cast<AAIController>(this->GetController());
		//aiController->RunBehaviorTree();
		GLog->Log("controller	");
	}

}

void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (aiController && aiController->GetBlackboardComponent()->GetValueAsBool(FName("DetectTowers"))) {
		Attack(Cast<ATowerBase>(aiController->GetBlackboardComponent()->GetValueAsObject(FName("DetectedTowers")));
	}


	/*DrawDebugLine(GetWorld(),Start,End,FColor::Green,false,1,0,1);
	bool IsSight = GetWorld()->LineTraceSingleByChannel(result,Start,End,ECC_Visibility,CollisionsParams);

	if (IsSight && result.GetActor()->IsA(ATowerBase::StaticClass())) {
		GLog->Log("you see me");
		aiController->GetBlackboardComponent()->SetValueAsBool(FName("DetectTowers"),true);

		Attack(Cast<ATowerBase>(result.GetActor()));
	}

	*/
	
}


void AEnemy::Attack(ATowerBase* tower) {
	targetTower = tower;
	isAttacking = true;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemy::Reload, 0.1f, true, 0.0f);
}

void AEnemy::Reload() {
	reloadTimer += 0.1f;

	if (reloadTimer > reloadTime) {
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		Attack(targetTower);
		reloadTimer = 0;
	}
}



