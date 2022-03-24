#include "MeleeAttackNotify.h"
#include "Enemy.h"
#include "TowerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Castle.h"
#include "MeleeBoss.h"

UMeleeAttackNotify::UMeleeAttackNotify() {
	cancelAttack = true;
}

void UMeleeAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (MeshComp->GetAttachmentRootActor()->IsA(AEnemy::StaticClass())) {
		if (cancelAttack) {
			cancelAttack = false;
			return;
		}

		AEnemy* enemy = Cast<AEnemy>(MeshComp->GetAttachmentRootActor());

		if (!enemy) {
			return;
		}

		float damage = enemy->attackDamage;

		if (enemy->targetTower) 
			enemy->targetTower->TowerTakeDamage(damage);
		else {
			AActor* actorCastle = UGameplayStatics::GetActorOfClass(MeshComp->GetAttachmentRootActor()->GetWorld(), ACastle::StaticClass());

			if (!actorCastle)
				return;

			ACastle* castle = Cast<ACastle>(actorCastle);
			castle->ApplyDamage(damage);
		}

		cancelAttack = !cancelAttack;
	}
}