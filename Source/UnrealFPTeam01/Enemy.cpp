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

AEnemy::AEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	health = 0.f;
	attackSpeed = 0.f;
	movementSpeed = 0.f;

	perceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = /*690.f*/520.f;
	sightConfig->LoseSightRadius = sightConfig->SightRadius + 500.f;
	sightConfig->PeripheralVisionAngleDegrees = 90.f;
	sightConfig->SetMaxAge(5.f);
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 900.f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	perceptionComp->SetDominantSense(*sightConfig->GetSenseImplementation());
	perceptionComp->ConfigureSense(*sightConfig);
 
	
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();	

	this->GetCharacterMovement()->MaxWalkSpeed = movementSpeed;

	perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy::OnSeeActor);
	if (this->GetController()->IsA(AAIController::StaticClass())) {
		aiController = Cast<AAIController>(this->GetController());
		aiController->SetPerceptionComponent(*perceptionComp);
	}
}

void AEnemy::OnSeeActor(AActor* actor, FAIStimulus stimulus) {
	
	ATowerBase* tower = Cast<ATowerBase>(actor);
	if (!aiController || !tower)
		return;

	GLog->Log("see " + actor->GetName());
	GLog->Log("from " + this->GetName());
	 
	aiController->GetBlackboardComponent()->SetValueAsBool(FName("DetectTowers"),stimulus.WasSuccessfullySensed());

	Attack(tower);
}

void AEnemy::Attack(ATowerBase* tower) {

	if (this->IsA(ARangeEnemy::StaticClass())) {
		ARangeEnemy* rangeEnemy = Cast<ARangeEnemy>(this);
		targetTower = tower;
		isAttacking = true;
		rangeEnemy->ballSpawnPosition = rangeEnemy->GetActorLocation() + rangeEnemy->GetActorRightVector() * -1 * 70;
		rangeEnemy->Shoot();
	}

	
}



