#include "MeleeBoss.h"

AMeleeBoss::AMeleeBoss() {
	attackDamage = initialDamage;
}

void AMeleeBoss::Attack(ATowerBase* tower) {

	if (isDuck) {
		attackDamage *= 2;

		if (tower != targetTower)
			attackDamage = initialDamage;
	}

	this->PlayAnimMontage(animMontage, 1, NAME_None);
	
	Super::Attack(tower);
}


void AMeleeBoss::TakeDamage(float damage) {
	Super::TakeDamage(damage);

	if (health <= 0) 
		waveController->OnKilledBoss();
	
}


