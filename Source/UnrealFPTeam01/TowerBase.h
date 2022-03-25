// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnrealFPTeam01/TowerProjectile.h"
#include "UnrealFPTeam01/Enemy.h"
#include "Blueprint/UserWidget.h"
#include "TowerBase.generated.h"

class AUnrealFPTeam01Character;

UENUM()
enum TowerState
{
	OnSide	UMETA(DisplayName = "On Side"),
	OnRoad	UMETA(DisplayName = "On Road")
};

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
	USceneComponent* ProjectileOrigin;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	float AttackCooldown;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitializeTower();

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	int TowerHealthOnRoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	int MaxTowerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	int TowerDamageOnRoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	float TowerRangeRadiusOnRoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TowerStats)
	float TowerAttackRateOnRoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	int TowerHealthOnSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	int TowerDamageOnSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	float TowerRangeRadiusOnSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	float TowerAttackRateOnSide;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> ActorsHit;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> IgnoreTargets;

	UPROPERTY()
	FHitResult UnderMouseHit;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> EndPathActors;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<TowerState> TowerState;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMaterialInterface*> BaseMeshMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* GreenMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* BlueMaterial;

	UPROPERTY(BlueprintReadWrite)
	AActor* EndPathActor;

	UPROPERTY(BlueprintReadWrite)
	FName TagOfEndPath;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AUnrealFPTeam01Character* PlayerRef;

	UPROPERTY(BlueprintReadWrite)
	bool isActive;

	UPROPERTY(BlueprintReadWrite)
	bool isInHand;

	UFUNCTION(BlueprintCallable)
	bool CheckHit();

	UFUNCTION(BlueprintCallable)
	void TowerTakeDamage(int damage);

	UFUNCTION(BlueprintCallable)
	void DestroyTower();

	UFUNCTION(BlueprintCallable)
	virtual void SetGreenPlacement();

	UFUNCTION(BlueprintCallable)
	virtual void SetBluePlacement();

	UFUNCTION(BlueprintCallable)
	virtual void SetMeshMaterials();

	UFUNCTION(BlueprintCallable)
	AActor* FindTarget(TArray<AActor*>& ActorsArray, TArray<AActor*>& TargetsToIgnore);

	UFUNCTION(BlueprintCallable)
	void RotateTowardTarget(AActor* target);

};

