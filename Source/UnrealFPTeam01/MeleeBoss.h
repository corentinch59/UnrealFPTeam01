#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MeleeBoss.generated.h"

UCLASS()
class UNREALFPTEAM01_API AMeleeBoss : public AEnemy {
	GENERATED_BODY()

public:

	AMeleeBoss();

	void Attack(ATowerBase* base) override;
	
	UPROPERTY(EditAnywhere)
	float initialDamage;

	UPROPERTY(EditAnywhere)
	float damage;

	UPROPERTY(EditAnywhere)
	bool isDuck;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* animMontage;
};
