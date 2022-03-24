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

	void TakeDamage(float damage) override;
	
	UPROPERTY(EditAnywhere)
	float initialDamage;

	UPROPERTY(EditAnywhere)
	bool isDuck;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* animMontage;

	UPROPERTY(EditAnywhere)
	AWaveController* waveController;

};
