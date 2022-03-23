// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnrealFPTeam01/PlateauInteractable.h"
#include "UnrealFPTeam01/TowerBox.h"
#include "UnrealFPTeam01Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class ATowerBase;
class AArcherTower;

UENUM()
enum TowerType
{
	None			UMETA(DisplayName = "None"),
	ArcherTower		UMETA(DisplayName = "Archer Tower"),
	KnightTower		UMETA(DisplayName = "Knight Tower")
};

UCLASS(config=Game)
class AUnrealFPTeam01Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly)
	ATowerBase* HeldTowerRef;

	UPROPERTY(VisibleDefaultsOnly)
	ATowerBase* ConstructTowerRef;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = TowersToSpawn)
	TSubclassOf<ATowerBase> ArcherTowerSpawn;

	UPROPERTY(EditAnywhere, Category = TowersToSpawn)
	TSubclassOf<ATowerBase> KnightTowerSpawn;

public:
	AUnrealFPTeam01Character();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	UPROPERTY(EditAnywhere, Category=CameraView)
	AActor* ExternalCam;

	UPROPERTY(EditAnywhere, Category=CameraView)
	float blendTime = .5f;

	UFUNCTION(BlueprintCallable)
	bool CheckHit();

	UFUNCTION(BlueprintCallable)
	void SwitchCamera();

	UFUNCTION(BlueprintCallable)
	void InteractWObject();

	UFUNCTION(BlueprintCallable)
	void ClearHand();

	UFUNCTION(BlueprintCallable)
	void ClearConstruction();

	UFUNCTION(BlueprintCallable)
	void ApplyConstruction();

	UPROPERTY(BlueprintReadWrite, Category=CameraView)
	bool isFP = true;

	UPROPERTY(BlueprintReadWrite)
	bool ConstructionMode = false;

	UPROPERTY(EditAnywhere, Category = PlayerStats)
	int NbTowerOnSide;

	UPROPERTY(EditAnywhere, Category = PlayerStats)
	int NbTowerOnRoad;

	UPROPERTY(EditAnywhere, Category = PlayerStats)
	int NbTowerMax;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<TowerType> TowerType;

protected:

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category=Interactions)
	float InteractionRange = 300.f;

	UPROPERTY(EditAnywhere, Category=Interactions)
	float InteractionRadius = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult interactableObj;

};

