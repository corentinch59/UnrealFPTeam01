// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealFPTeam01Character.h"
#include "UnrealFPTeam01Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealFPTeam01/ArcherTower.h"
#include "UnrealFPTeam01/TowerBase.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUnrealFPTeam01Character

AUnrealFPTeam01Character::AUnrealFPTeam01Character()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Get every tower meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArcherTowerAsset(TEXT("/Game/FirstPerson/GA/Characters/tour_archer"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> KnightTowerAsset(TEXT("/Game/FirstPerson/GA/Characters/chevalier_fix"));

	// Setup the meshes that will be held
	TowerInHand = CreateDefaultSubobject<USceneComponent>(TEXT("TowerInHand"));
	TowerInHand->SetupAttachment(RootComponent);
	TowerInHand->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Setup for the ArcherTower
	TowerInHand->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	TowerInHand->SetRelativeLocation(FVector(-35.f, 27.f, 0.f));
	TowerInHand->SetRelativeRotation(FRotator(10.f,0.f,0.f));

	ArcherTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArcherTowerMesh"));
	ArcherTowerMesh->SetupAttachment(RootComponent);
	ArcherTowerMesh->AttachToComponent(TowerInHand, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	ArcherTowerMesh->SetStaticMesh(ArcherTowerAsset.Object);

	KnightTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KnightTowerMesh"));
	KnightTowerMesh->SetupAttachment(RootComponent);
	KnightTowerMesh->AttachToComponent(TowerInHand, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	KnightTowerMesh->SetStaticMesh(KnightTowerAsset.Object);
}

void AUnrealFPTeam01Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetVisibility(false);
	ArcherTowerMesh->SetVisibility(false);

}

//////////////////////////////////////////////////////////////////////////
// Input

bool AUnrealFPTeam01Character::CheckHit()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectsTypeQuery;
	ObjectsTypeQuery.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	FVector CameraLocation = FirstPersonCameraComponent->GetComponentLocation();

	FVector EndLocation = (FirstPersonCameraComponent->GetForwardVector() * InteractionRange) + CameraLocation;

	bool hasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), CameraLocation, EndLocation, InteractionRadius, ObjectsTypeQuery, false, IgnoredActors, EDrawDebugTrace::None, interactableObj, true);

	return hasHit;
}

void AUnrealFPTeam01Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnrealFPTeam01Character::OnResetVR);

	// Bind gameplay Input
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUnrealFPTeam01Character::InteractWObject);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealFPTeam01Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealFPTeam01Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealFPTeam01Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealFPTeam01Character::LookUpAtRate);
}

void AUnrealFPTeam01Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUnrealFPTeam01Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUnrealFPTeam01Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUnrealFPTeam01Character::SwitchCamera()
{
	switch (isFP)
	{
	case false:
		/* Switch from Tabletop Camera to First Person Camera */
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, blendTime, VTBlend_Linear, 0, false);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("First Person Camera %f"), GetWorld()->TimeSeconds));
		/* Enable Looking and Moving inputs */
		GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(false);
		GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(false);
		/* Disable mouse cursor */
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

		isFP = true;

		break;
	default:
		/* Switch from First Person Camera to Tabletop Camera */
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(ExternalCam, blendTime, VTBlend_Linear, 0, false);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Tabletop Camera %f"), GetWorld()->TimeSeconds));
		/* Disable Looking and Moving inputs */
		GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(true);
		GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);
		/* Show the mouse cursor */
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		isFP = false;

		break;
	}
}

void AUnrealFPTeam01Character::InteractWObject()
{
	AActor* ActorHit = Cast<APlateauInteractable>(interactableObj.Actor);
	if(ActorHit && isFP)
	{
		SwitchCamera();
		return;
	}

	if(!isFP)
	{
		SwitchCamera();
			return;
	}

	ATowerBox* TowerBox = Cast<ATowerBox>(interactableObj.Actor);
	if (TowerBox)
	{
		TowerHeldType = TowerBox->BoxType;

	}
}

void AUnrealFPTeam01Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealFPTeam01Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealFPTeam01Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
