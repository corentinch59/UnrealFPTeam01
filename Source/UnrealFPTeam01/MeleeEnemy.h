	#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class UNREALFPTEAM01_API AMeleeEnemy : public AEnemy {
	GENERATED_BODY()

public:
	AMeleeEnemy();

	void Attack(ATowerBase* base) override;

};
