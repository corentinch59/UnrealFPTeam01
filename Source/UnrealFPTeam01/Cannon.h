#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Cannon.generated.h"


UCLASS()
class UNREALFPTEAM01_API ACannon : public AEnemy
{
	GENERATED_BODY()

public:
	ACannon();

	UPROPERTY(EditAnywhere)
	float reloadTime;

	UPROPERTY(EditAnywhere)
	float ballSpeed;

protected:
	virtual void Tick(float deltaTime) override;

	virtual void OnSeeActor(AActor* actor, FAIStimulus stimulus) override;
};
