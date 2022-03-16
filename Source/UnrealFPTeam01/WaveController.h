#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveConfig.h"
#include "WaveController.generated.h"

UCLASS()
class UNREALFPTEAM01_API AWaveController : public AActor {
	GENERATED_BODY()
	
public:	
	AWaveController();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<FUWaveConfig> waves;

	UPROPERTY(EditAnywhere)
	int actualWaveId;

	UPROPERTY(EditAnywhere)
	AActor* enemySpawn;

	UPROPERTY(EditAnywhere)
	AActor* enemyEnd;

	UPROPERTY(EditAnywhere)
	FUWaveConfig actualWave;

	UPROPERTY(EditAnywhere)
	float timeBetweenSpawn;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USceneComponent* sceneComp;

	UFUNCTION()
	void SpawnWave();

	UFUNCTION()
	void SpawnEnemy();

	UPROPERTY()
	FTimerHandle timerHandle;

	UPROPERTY()
	float waveTimer;
};
