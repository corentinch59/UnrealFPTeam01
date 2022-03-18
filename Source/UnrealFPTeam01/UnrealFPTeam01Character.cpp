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

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);


	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	HeldTower = nullptr;
}

void AUnrealFPTeam01Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	
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
	FRotator CameraRotation = FirstPersonCameraComponent->GetRelativeRotation();

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

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AUnrealFPTeam01Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

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
