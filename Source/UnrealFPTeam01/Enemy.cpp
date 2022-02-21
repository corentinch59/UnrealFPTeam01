#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig.h"	
#include "Containers/Array.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Cannon.h"

AEnemy::AEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	health = 0.f;
	attackSpeed = 0.f;
	movementSpeed = 0.f;

	perceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = 1000.f;
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
	GLog->Log("see " + actor->GetName());
	GLog->Log("from " + this->GetName());
	
	if (!aiController)
		return;
	 
	aiController->GetBlackboardComponent()->SetValueAsBool(FName("DetectTowers"),stimulus.WasSuccessfullySensed());

	Attack();
}

void AEnemy::Attack() {
	GLog->Log("my attack");

	if (this->IsA(Cannon::StaticClass())) {

	}
}



