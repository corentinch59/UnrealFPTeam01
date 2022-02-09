// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateauInteractable.h"

// Sets default values
APlateauInteractable::APlateauInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

