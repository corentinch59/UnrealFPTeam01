	#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class UNREALFPTEAM01_API AMeleeEnemy : public AEnemy {
	GENERATED_BODY()

public:
	AMeleeEnemy();

	void Attack(ATowerBase* base) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* weapon;

};
