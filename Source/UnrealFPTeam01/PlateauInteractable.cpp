// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateauInteractable.h"


// Sets default values
APlateauInteractable::APlateauInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	TabletopCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TableTop Camera"));
	TabletopCamera->SetupAttachment(MeshComponent);
	TabletopCamera->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	TabletopCamera->SetRelativeRotation(FRotator(-90.f,180.f,180.f));
}

void APlateauInteractable::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void APlateauInteractable::OnOverlapEnd(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherIndex)
{

}

// Called when the game starts or when spawned
void APlateauInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlateauInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

