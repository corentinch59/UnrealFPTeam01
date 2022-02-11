#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig.h"	
#include "Containers/Array.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy::OnSeeActor);
	perceptionComp->ConfigureSense(*sightConfig);
	
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();	

	this->GetCharacterMovement()->MaxWalkSpeed = movementSpeed;

	if (this->GetController()->IsA(AAIController::StaticClass())) {
		AAIController* controller = Cast<AAIController>(this->GetController());
		perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy::OnSeeActor);
		controller->SetPerceptionComponent(*perceptionComp);
	}
	
}

void AEnemy::OnSeeActor(AActor* actor, FAIStimulus stimulus) {
	GLog->Log("Log me " + actor->GetName());


}



