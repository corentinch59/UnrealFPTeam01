#include "Cannon.h"

ACannon::ACannon() {
	PrimaryActorTick.bCanEverTick = true;
}

void ACannon::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	

}

void OnSeeActor(AActor* actor, FAIStimulus stimulus) {
	GLog->Log("cannon see");
}