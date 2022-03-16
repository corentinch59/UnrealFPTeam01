#include "WaveController.h"

AWaveController::AWaveController() {
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));

}

void AWaveController::BeginPlay() {
	Super::BeginPlay();

	GLog->Log("begin play");
	SpawnWave();
	
}

void AWaveController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AWaveController::SpawnWave() {
	if (actualWaveId < waves.Num()) { // on peut lancer la wave

		actualWave = waves[actualWaveId];

		actualWaveId++;
		GLog->Log("Spawn Wave");
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::SpawnEnemy, 0.1f, true, 0.0f);
	}
}

void AWaveController::SpawnEnemy() {
	waveTimer++;

	if (waveTimer >= timeBetweenSpawn) {

		AEnemy* enemy = Cast<AEnemy>(GetWorld()->SpawnActor<AEnemy>(actualWave.ennemiesInWave[0], enemySpawn->GetActorLocation(), FRotator(0, 0, 0)));
		enemy->endPatrolActor = enemyEnd;
		//enemy->AIControllerClass
		GLog->Log("Spawn enemy");
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		waveTimer = 0;
	}
}