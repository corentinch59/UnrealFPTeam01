#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "RangeEnemy.generated.h"

UCLASS()
class UNREALFPTEAM01_API ARangeEnemy : public AEnemy {
	GENERATED_BODY()

public:
	ARangeEnemy();

	UPROPERTY(EditAnywhere)
	float ballSpeed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUnrealFPTeam01Projectile> ballClass;

	UPROPERTY(EditAnywhere)
	FVector offsetBallSpawn;

	UPROPERTY(EditAnywhere)
	FVector ballSize;

	UPROPERTY(VisibleAnywhere)
	FVector ballSpawnPosition;

	UPROPERTY(EditAnywhere)
	class UMaterial* ballMaterial;

	UPROPERTY(EditAnywhere)
	bool isCannon;

	UPROPERTY(EditAnywhere)
	UActorComponent* ballStart;

	void Attack(ATowerBase* base) override;

protected:
	virtual void Tick(float deltaTime) override;


};

