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

    UPROPERTY(VisibleAnywhere)
    ATowerBase* targetTower;

    UFUNCTION()
    virtual void Attack(ATowerBase* tower);

    UFUNCTION()
    virtual void Reload();

    UFUNCTION()
    void TakeDamage(float damage);
    
protected:
	virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    FTimerHandle timerHandle;


private:

    UPROPERTY()
    AAIController* aiController;

    UPROPERTY()
    float reloadTimer;


    UPROPERTY()
    USceneComponent* sceneComp;
};
