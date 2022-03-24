#include "DialogAction.h"
#include "ArcherTower.h"
#include "DialogController.h"
#include "Kismet/GameplayStatics.h"

UDialogAction::UDialogAction() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UDialogAction::BeginPlay() {
	Super::BeginPlay();

	if (dialogType != DialogType::SPAWN)
		return;

	dialogController = Cast<ADialogController>(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogController::StaticClass()));
	int index = FMath::RandRange(0,sounds.Num() - 1);

	if (!GetWorld() || !sounds[index])
		return;

	dialogController->OnDialogSpawned(dialogs[index],sounds[index]);
}


void UDialogAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


