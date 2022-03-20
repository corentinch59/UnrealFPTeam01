#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy.h"
#include "WaveConfig.generated.h"

USTRUCT()
struct UNREALFPTEAM01_API FUWaveConfig /*: public UObject*/ {
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int waveId;

	UPROPERTY(EditAnywhere)
	TArray<class TSubclassOf<AEnemy>> ennemiesInWave;


	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<AEnemy>> spawnedEnnemies;
	
};
