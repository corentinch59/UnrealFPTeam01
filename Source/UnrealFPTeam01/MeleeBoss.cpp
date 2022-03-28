#include "MeleeBoss.h"
#include "Kismet/GameplayStatics.h"
#include "WaveController.h"

AMeleeBoss::AMeleeBoss() {
	attackDamage = initialDamage;
}

void AMeleeBoss::BeginPlay() {
	Super::BeginPlay();
	waveController = Cast<AWaveController>(UGameplayStatics::GetActorOfClass(GetWorld(), AWaveController::StaticClass()));
}

void AMeleeBoss::Attack(ATowerBase* tower) {

	if (isDuck) {
		attackDamage *= 2;

		if (tower != targetTower)
			attackDamage = initialDamage;
	}
	
	Super::Attack(tower);
}


void AMeleeBoss::ApplyDamage(float damage) {
	Super::ApplyDamage(damage);

	if (health <= 0) 
		waveController->OnKilledBoss();
	
}


