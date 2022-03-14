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
	float attackDamage;

	UPROPERTY(EditAnywhere)
	float reloadTime;

	UPROPERTY(EditAnywhere)
	float ballSpeed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUnrealFPTeam01Projectile> ballClass;

	UPROPERTY(VisibleAnywhere)
	FVector ballSpawnPosition;

	UPROPERTY(EditAnywhere)
	class UMaterial* ballMaterial;

	void Shoot();

	void Reload();

protected:
	virtual void Tick(float deltaTime) override;

private:
	UPROPERTY()
	float reloadTimer;

	UPROPERTY()
	FTimerHandle timerHandle;
};
