#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Cannon.generated.h"


UCLASS()
class UNREALFPTEAM01_API ACannon : public AEnemy {

	GENERATED_BODY()

public:
	ACannon();

	UPROPERTY(EditAnywhere)
	float reloadTime;

	UPROPERTY(EditAnywhere)
	float ballSpeed;

	UPROPERTY(VisibleAnywhere)
	bool isAttacking;

	UPROPERTY(VisibleAnywhere)
	AActor* targetTower;

	void Shoot();

protected:
	virtual void Tick(float deltaTime) override;
};
