#include "Castle.h"

ACastle::ACastle() {
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = meshComp;

}

void ACastle::BeginPlay() {
	Super::BeginPlay();
	
}

void ACastle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ACastle::ApplyDamage(float damage) {

	health -= damage;
	GLog->Log("Apply damage");

	if (health <= 0) {
		Destroy();
		// Anim de fin de jeu
	}
}

