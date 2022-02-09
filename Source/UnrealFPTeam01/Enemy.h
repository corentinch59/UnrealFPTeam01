#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALFPTEAM01_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

    UPROPERTY(EditAnywhere)
    float health;

    UPROPERTY(EditAnywhere)
    float movementSpeed;

    UPROPERTY(EditAnywhere)
    float attackSpeed;

protected:
	virtual void BeginPlay() override;

public:	

};
