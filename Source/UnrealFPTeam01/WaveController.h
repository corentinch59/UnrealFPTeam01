#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveConfig.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/UserWidget.h"
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

	UPROPERTY()
	FVector enemySpawn;

	UPROPERTY()
	FVector enemyEnd;

	UPROPERTY(EditAnywhere)
	FUWaveConfig actualWave;

	UPROPERTY(EditAnywhere)
	float timeBetweenSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeBetweenWave;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> splines;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* enemyTree;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AController> enemyController;

	UPROPERTY()
	AAIController* enemyAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isWaitingWave;

//	UPROPERTY(EditAnywhere)
//	TSubclassOf<UUserWidget> waveWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaitWaveEvent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USceneComponent* sceneComp;

	UFUNCTION()
	void SpawnWave();

	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void WaitNextWave();

	UPROPERTY()
	FTimerHandle timerHandle;

	UPROPERTY()
	float waveTimer;

	UPROPERTY()
	bool generateWave;

	UPROPERTY()
	float initTimeBetweenWave;
};
