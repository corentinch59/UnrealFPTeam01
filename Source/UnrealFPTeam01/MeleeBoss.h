#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "WaveController.h"
#include "MeleeBoss.generated.h"

UCLASS()
class UNREALFPTEAM01_API AMeleeBoss : public AEnemy {
	GENERATED_BODY()

public:

	AMeleeBoss();

	void Attack(ATowerBase* base) override;

//	virtual void BeginPlay() override;

	void ApplyDamage(float damage) override;
	
	UPROPERTY(EditAnywhere)
	float initialDamage;

	UPROPERTY(EditAnywhere)
	bool isDuck;

	UPROPERTY(EditAnywhere)
	AWaveController* waveController;

protected: 
	virtual void BeginPlay() override;
};
