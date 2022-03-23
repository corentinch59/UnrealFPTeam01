#include "DialogAction.h"
#include "ArcherTower.h"
#include "Kismet/GameplayStatics.h"

UDialogAction::UDialogAction() {
	PrimaryComponentTick.bCanEverTick = true;

}


void UDialogAction::BeginPlay() {
	Super::BeginPlay();

	int index = FMath::RandRange(0,sounds.Num());

	if (!GetWorld() || !sounds[index])
		return;

	UGameplayStatics::PlaySound2D(GetWorld(), sounds[index], 1.f, 1.f, 0.f);

	//AArcherTower::OnDialogSpawned(dialogs[index]);
	dialogController->OnDialogSpawned(dialogs[index]);
}


void UDialogAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


