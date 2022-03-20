#include "WaveController.h"

AWaveController::AWaveController() {
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	generateWave = true;

	timeBetweenWave = initTimeBetweenWave;
}

void AWaveController::BeginPlay() {
	Super::BeginPlay();

	if (splineActor && splineActor->GetComponentByClass(USplineComponent::StaticClass())) {
		USplineComponent* splineComp = Cast<USplineComponent>(splineActor->GetComponentByClass(USplineComponent::StaticClass()));

		if (!splineComp) 
			return;
		

		enemySpawn = splineComp->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		enemyEnd = splineComp->GetLocationAtSplinePoint(splineComp->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	}

	SpawnWave();
	
}

void AWaveController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AWaveController::SpawnWave() {
	if (actualWaveId < waves.Num()) { 

		if(generateWave) 
			actualWave = waves[actualWaveId];

		//actualWaveId++;
		generateWave = false;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::SpawnEnemy, 0.1f, true, 0.0f);
	}
}

void AWaveController::SpawnEnemy() {
	waveTimer += 0.1f;

	if (waveTimer >= timeBetweenSpawn) {
		int enemyToSpawnIndex = actualWave.spawnedEnnemies.Num();

		if (enemyToSpawnIndex < actualWave.ennemiesInWave.Num()) {
			AEnemy* enemy = Cast<AEnemy>(GetWorld()->SpawnActor<AEnemy>(actualWave.ennemiesInWave[enemyToSpawnIndex], enemySpawn, FRotator(0, 0, 0)));
		//	enemyAI = GetWorld()->SpawnActor<AAIController>(enemyController, enemySpawn, FRotator(0, 0, 0));
			
		//	enemyAI->Possess(enemy);
			//enemyAI->Possess();
			
			actualWave.spawnedEnnemies.Add(actualWave.ennemiesInWave[enemyToSpawnIndex]);
			GLog->Log("spawned");
			GetWorld()->GetTimerManager().ClearTimer(timerHandle);
			waveTimer = 0;
			SpawnWave();
		}
		else { // On passe à la vague suivante
			GLog->Log("next wave");
			isWaitingWave = true;
			OnWaitWaveEvent();
			GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::WaitNextWave, 1.0f, true, 0.0f);
		}

	}
}

void AWaveController::WaitNextWave() {
	timeBetweenWave--;

	GLog->Log(FString::FromInt(timeBetweenWave));

	if (timeBetweenWave <= 0) {
		
		timeBetweenWave = initTimeBetweenWave;
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		actualWaveId++;
		isWaitingWave = false;
		generateWave = true;
		SpawnWave();
	}
}