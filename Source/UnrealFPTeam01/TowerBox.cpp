// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBox.h"



// Sets default values
ATowerBox::ATowerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATowerBox::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATowerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

