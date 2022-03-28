#include "WaveController.h"
#include "DialogAction.h"
#include "Kismet/GameplayStatics.h"

AWaveController::AWaveController() {
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	generateWave = true;

	timeBetweenWave = initTimeBetweenWave;
}

void AWaveController::BeginPlay() {
	Super::BeginPlay();
	dialogController = Cast<ADialogController>(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogController::StaticClass()));
	
	GLog->Log(FString::FromInt(timeBeforeWave));
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::SpawnWave, 1.f, true, timeBeforeWave);

}

void AWaveController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AWaveController::SpawnWave() {
	if (actualWaveId < waves.Num()) {
		GLog->Log("spawned wave");
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		if (generateWave) {
			actualWave = waves[actualWaveId];
			UDialogAction* currentDialogAction = Cast<UDialogAction>(this->GetComponentsByClass(UDialogAction::StaticClass())[(this->GetComponentsByClass(UDialogAction::StaticClass()).Num() - 1 )  - actualWaveId]);

			GLog->Log(currentDialogAction->dialogs[0].ToString());


			if (currentDialogAction && dialogController)
				dialogController->OnDialogSpawned(currentDialogAction->dialogs[0], currentDialogAction->sounds[0]);
		}


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

			enemy->SetActorScale3D(enemy->enemyScale);
			enemy->aiController = enemyAI;
			
			actualWave.spawnedEnnemies.Add(actualWave.ennemiesInWave[enemyToSpawnIndex]);
			GLog->Log("spawned");
			GetWorld()->GetTimerManager().ClearTimer(timerHandle);
			waveTimer = 0;
			SpawnWave();
		}
	}
}

void AWaveController::RefreshKilledEnnemies() {
	killedEnnemies++;

	GLog->Log("refresh kill");

	if (killedEnnemies >= actualWave.ennemiesInWave.Num()) {
		if (waves.Num() <= 1)
			return;

		GLog->Log("next wave");
		isWaitingWave = true;
		OnBeginWaitWave();

		UDialogAction* currentDialogAction = Cast<UDialogAction>(this->GetComponentsByClass(UDialogAction::StaticClass())[(actualWaveId)+(waves.Num() - 1)]);

		if (currentDialogAction)
			dialogController->OnDialogSpawned(currentDialogAction->dialogs[0], currentDialogAction->sounds[0]);
		

		GLog->Log(FString::FromInt((actualWaveId) + (waves.Num() - 1)));
		GLog->Log("--------");

		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWaveController::WaitNextWave, 1.0f, true, 0.0f);
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