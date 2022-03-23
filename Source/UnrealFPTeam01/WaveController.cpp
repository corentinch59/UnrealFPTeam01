#include "WaveController.h"

AWaveController::AWaveController() {
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	generateWave = true;

	timeBetweenWave = initTimeBetweenWave;
}

void AWaveController::BeginPlay() {
	Super::BeginPlay();

	/*if (splineActor && splineActor->GetComponentByClass(USplineComponent::StaticClass())) {
		USplineComponent* splineComp = Cast<USplineComponent>(splineActor->GetComponentByClass(USplineComponent::StaticClass()));

		if (!splineComp) 
			return;
		

		enemySpawn = splineComp->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		enemyEnd = splineComp->GetLocationAtSplinePoint(splineComp->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	}
	*/

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

			int splineIndex = FMath::RandRange(0, splines.Num() - 1);

			if (!splines[splineIndex] && !splines[splineIndex]->GetComponentByClass(USplineComponent::StaticClass())) {
				GLog->Log("error with spline list");
				return;
			}

			USplineComponent* targetSpline = Cast<USplineComponent>(splines[splineIndex]->GetComponentByClass(USplineComponent::StaticClass()));

			if (!targetSpline)
				return;

			enemySpawn = targetSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);

			AEnemy* enemy = Cast<AEnemy>(GetWorld()->SpawnActor<AEnemy>(actualWave.ennemiesInWave[enemyToSpawnIndex], enemySpawn, FRotator(0, 0, 0)));

			enemy->targetSpline = targetSpline;

			enemyAI = GetWorld()->SpawnActor<AAIController>(enemyController, enemySpawn, FRotator(0, 0, 0));
			
			enemyAI->Possess(enemy);
			//enemyAI->Possess();

			enemy->SetActorScale3D(enemy->enemyScale);
			
			actualWave.spawnedEnnemies.Add(actualWave.ennemiesInWave[enemyToSpawnIndex]);
			GLog->Log("spawned");
			GetWorld()->GetTimerManager().ClearTimer(timerHandle);
			waveTimer = 0;
			SpawnWave();
		}
		else { // On passe à la vague suivante

			if (waves.Num() <= 1)
				return;

			GLog->Log("next wave");
			isWaitingWave = true;
			OnBeginWaitWave();
			GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::WaitNextWave, 1.0f, true, 0.0f);
		}

	}
}

void AWaveController::WaitNextWave() {
	timeBetweenWave--;

	GLog->Log(FString::FromInt(timeBetweenWave));
	OnTickWaitWave(timeBetweenWave);

	if (timeBetweenWave <= 0) {
		
		timeBetweenWave = initTimeBetweenWave;
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		actualWaveId++;
		isWaitingWave = false;
		generateWave = true;
		OnEndWaitWave();
		SpawnWave();
	}
}