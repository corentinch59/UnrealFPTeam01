#include "SetEnemyTargetLocation.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

USetEnemyTargetLocation::USetEnemyTargetLocation() {
	bNotifyTick = true;
}

void USetEnemyTargetLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	if (OwnerComp.GetOwner()->GetInstigatorController()->GetPawn()->IsA(AEnemy::StaticClass())) {
		AEnemy* targetEnemy = Cast<AEnemy>(OwnerComp.GetOwner()->GetInstigatorController()->GetPawn());
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", targetEnemy->endPatrolActor->GetActorLocation());
		this->FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
		this->FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	
}

void USetEnemyTargetLocation::OnGameplayTaskActivated(UGameplayTask& Task) {}
void USetEnemyTargetLocation::OnGameplayTaskDeactivated(UGameplayTask& Task) {}
void USetEnemyTargetLocation::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) {}
EBTNodeResult::Type USetEnemyTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) { return EBTNodeResult::InProgress; }
