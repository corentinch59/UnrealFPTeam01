// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnrealFPTeam01/TowerProjectile.h"
#include "TowerBase.generated.h"

UCLASS()
class UNREALFPTEAM01_API ATowerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBase();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ATowerProjectile> TowerProjectile;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileOrigin;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	int TowerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	int TowerDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	float TowerRangeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	float TowerAttackRate;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> ActorsHit;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> EndPathActors;

	UPROPERTY(BlueprintReadWrite)
	AActor* EndPathActor;

	UPROPERTY(BlueprintReadWrite)
	FName TagOfEndPath;

	UPROPERTY(BlueprintReadWrite)
	bool bIsOnRoad;

	UFUNCTION(BlueprintCallable)
	bool CheckHit();

	UFUNCTION(BlueprintCallable)
	void TowerTakeDamage(int damage);

	UFUNCTION(BlueprintCallable)
	void DestroyTower();

	UFUNCTION(BlueprintCallable)
	AActor* FindTarget(TArray<AActor*>& ActorsArray);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
