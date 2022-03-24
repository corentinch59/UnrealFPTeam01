#include "MeleeEnemy.h"

AMeleeEnemy::AMeleeEnemy() {
	
}

void AMeleeEnemy::Attack(ATowerBase* tower) {
	//this->PlayAnimMontage(animMontage, 1, NAME_None);

	Super::Attack(tower);
}
