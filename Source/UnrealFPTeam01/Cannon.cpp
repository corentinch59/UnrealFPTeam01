#include "Cannon.h"

ACannon::ACannon() {
	PrimaryActorTick.bCanEverTick = true;

}

void ACannon::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (isAttacking) {
		GLog->Log(targetTower->GetActorRotation().ToString());
		this->SetActorRotation(FRotator(0,-90,0), ETeleportType::ResetPhysics);
	}
}

void ACannon::Shoot() {
	GLog->Log("Attack");


}