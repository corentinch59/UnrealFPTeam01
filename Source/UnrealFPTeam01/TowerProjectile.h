// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TowerProjectile.generated.h"


UCLASS()
class UNREALFPTEAM01_API ATowerProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATowerProjectile();


	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	float lifeTime;

	UPROPERTY(EditAnywhere)
	float SpawnTime;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere)
	float AngleOffset;

	UFUNCTION()
	void InitializeProjectile(AActor* targetToSet, float time = 0.f, float offset = 0.f);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
