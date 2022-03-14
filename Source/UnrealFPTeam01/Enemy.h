#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
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


protected:
	virtual void BeginPlay() override;

private:
    UPROPERTY()
    class UAISenseConfig_Sight* sightConfig;

    UPROPERTY()
    AAIController* aiController;

    UFUNCTION()
    void OnSeeActor(AActor* actor, FAIStimulus stimulus);

    UFUNCTION()
    virtual void Attack(ATowerBase* tower);
};
