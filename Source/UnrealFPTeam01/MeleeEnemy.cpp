#include "MeleeEnemy.h"

AMeleeEnemy::AMeleeEnemy() {
	
}

void AMeleeEnemy::Attack(ATowerBase* tower) {
	AEnemy::Attack(tower);
}
