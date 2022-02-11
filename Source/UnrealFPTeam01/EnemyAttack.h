#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "HAL/Platform.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyAttack.generated.h"


UCLASS()
class UNREALFPTEAM01_API UEnemyAttack : public UBTTask_BlackboardBase {
	GENERATED_BODY()

public:
	UEnemyAttack();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UBehaviorTree* Tree;
	class ABMAIController* Controller;
	class ABMBossCharacter* Character;
	
};
