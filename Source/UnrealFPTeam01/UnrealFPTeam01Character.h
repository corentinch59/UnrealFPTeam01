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
	USceneComponent* TowerInHand;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* ArcherTowerMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* KnightTowerMesh;

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

	UPROPERTY()
	TEnumAsByte<BoxType> TowerHeldType;

	UFUNCTION(BlueprintCallable)
	bool CheckHit();

	UFUNCTION(BlueprintCallable)
	void SwitchCamera();

	UFUNCTION(BlueprintCallable)
	void InteractWObject();

	UPROPERTY(BlueprintReadWrite, Category=CameraView)
	bool isFP = true;

	UPROPERTY(VisibleDefaultsOnly)
	int TowerOnSide;

	UPROPERTY(VisibleDefaultsOnly)
	int TowerOnRoad;

	UPROPERTY(VisibleDefaultsOnly)
	int nbTowerMax;

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

