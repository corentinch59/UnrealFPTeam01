#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/SplineComponent.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class UNREALFPTEAM01_API AEnemy : public ACharacter {
	GENERATED_BODY()

public:
	AEnemy();

    UPROPERTY(EditAnywhere)
    float health;

    UPROPERTY(EditAnywhere)
    float maxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float movementSpeed;

    UPROPERTY(EditAnywhere)
    float attackSpeed;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float attackDamage;

    UPROPERTY(EditAnywhere)
    float reloadTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float sightRange;

    UPROPERTY(VisibleAnywhere)
    bool isAttacking;

    UPROPERTY(EditAnywhere)
    FVector enemyScale;

    UPROPERTY(VisibleAnywhere)
    ATowerBase* targetTower;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    USplineComponent* targetSpline;

    UFUNCTION()
    virtual void Attack(ATowerBase* tower);

    UFUNCTION()
    virtual void Reload();

    UFUNCTION()
    void TakeDamage(float damage);


    UPROPERTY()
    AAIController* aiController;
protected:
	virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;


    UPROPERTY()
    FTimerHandle timerHandle;



private:


    UPROPERTY()
    float reloadTimer;


    UPROPERTY()
    USceneComponent* sceneComp;
};
