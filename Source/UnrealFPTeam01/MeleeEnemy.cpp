#include "MeleeEnemy.h"

AMeleeEnemy::AMeleeEnemy() {
	
}

void AMeleeEnemy::Attack(ATowerBase* tower) {
	//this->PlayAnimMontage(animMontage, 1, NAME_None);
	GLog->Log("Attack Melee Enemy");
	Super::Attack(tower);
}
