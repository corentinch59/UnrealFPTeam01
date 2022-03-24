#include "MeleeBoss.h"

AMeleeBoss::AMeleeBoss() {
	damage = initialDamage;
}

void AMeleeBoss::Attack(ATowerBase* tower) {	
	if (isDuck) {
		damage *= 2;

		if (tower != targetTower)
			damage = initialDamage;
	}

	// Play montage
	this->PlayAnimMontage(animMontage,1,NAME_None);
	AEnemy::Attack(tower);
}



