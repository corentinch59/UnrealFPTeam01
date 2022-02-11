#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
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

    UPROPERTY(VisibleAnywhere)
    UAIPerceptionComponent* perceptionComp;

    UPROPERTY(EditAnywhere)
    AActor* endPatrolActor;

    UFUNCTION()
    void OnSeeActor(AActor* actor, FAIStimulus stimulus);

protected:
	virtual void BeginPlay() override;

private:

    UPROPERTY()
    class UAISenseConfig_Sight* sightConfig;

};
