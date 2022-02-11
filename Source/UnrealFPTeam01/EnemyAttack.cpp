#include "EnemyAttack.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UEnemyAttack::UEnemyAttack() {
	bNotifyTick = true;
}

void UEnemyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	//GLog->Log("Possess"); 

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("First Person Camera %f"), GetWorld()->TimeSeconds));
	
}


void UEnemyAttack::OnGameplayTaskActivated(UGameplayTask& Task) {}

void UEnemyAttack::OnGameplayTaskDeactivated(UGameplayTask& Task) {}

void UEnemyAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) {}

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) { return EBTNodeResult::InProgress;}
