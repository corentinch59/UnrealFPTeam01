#include "DialogAction.h"
#include "Kismet/GameplayStatics.h"

UDialogAction::UDialogAction() {
	PrimaryComponentTick.bCanEverTick = true;

}


void UDialogAction::BeginPlay() {
	Super::BeginPlay();

	int index = FMath::RandRange(0,sounds.Num());
	UGameplayStatics::PlaySound2D(GetWorld(), sounds[index], 1.f, 1.f, 0.f);


}


void UDialogAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

