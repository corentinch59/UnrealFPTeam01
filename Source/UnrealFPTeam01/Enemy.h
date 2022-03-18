#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class UNREALFPTEAM01_API AEnemy : public ACharacter {
	GENERATED_BODY()

public:
	AEnemy();

    UPROPERTY(EditAnywhere)
    float health;

    UPROPERTY(EditAnywhere)
    float movementSpeed;

    UPROPERTY(EditAnywhere)
    float attackSpeed;

    UPROPERTY(EditAnywhere)
    float reloadTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float sightRange;

    UPROPERTY(EditAnywhere)
    AActor* endPatrolActor;

    UPROPERTY(VisibleAnywhere)
    bool isAttacking;

    UPROPERTY(VisibleAnywhere)
    ATowerBase* targetTower;

    UFUNCTION()
    virtual void Attack(ATowerBase* tower);

    UFUNCTION()
    virtual void Reload();

protected:
	virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

private:

    UPROPERTY()
    AAIController* aiController;

    UPROPERTY()
    float reloadTimer;

    UPROPERTY()
    FTimerHandle timerHandle;

    UPROPERTY()
    USceneComponent* sceneComp;
};
