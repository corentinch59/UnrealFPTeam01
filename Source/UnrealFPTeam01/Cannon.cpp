#include "Cannon.h"

ACannon::ACannon() {
	PrimaryActorTick.bCanEverTick = true;

}

void ACannon::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}
