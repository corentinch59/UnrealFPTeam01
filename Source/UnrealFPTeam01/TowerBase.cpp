// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "UnrealFPTeam01/UnrealFPTeam01Character.h"
#include "UnrealFPTeam01/PlateauInteractable.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionProfileName(TEXT("TowerP"));

	RootComponent = MeshComponent;

	ProjectileOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileOrigin"));
	ProjectileOrigin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	ProjectileOrigin->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	TowerHealth = 100;
	TowerDamage = 1;
	TowerRangeRadius = 250.f;
	TowerAttackRate = 1.f;
	TagOfEndPath = "EndPath";
	isActive = true;
	isInHand = false;
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	MeshComponent->OnClicked.AddDynamic(this, &ATowerBase::OnClicked);

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagOfEndPath, EndPathActors);
	if(EndPathActors.Num() > 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Too many End Paths ! %f"), GetWorld()->TimeSeconds));
	}
	EndPathActor = EndPathActors[0];
	if(EndPathActor != nullptr)
	{
		GLog->Log(this->GetName() + ": End Path Set");
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Couldn't find End Path ! %f"), GetWorld()->TimeSeconds));
	}

	for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
	{
		BaseMeshMaterial.Add(MeshComponent->GetMaterial(i));
	}

	/*GLog->Log("Number of Base Materials : " + FString::FromInt(BaseMeshMaterial.Num()));
	GLog->Log(BaseMeshMaterial[0]->GetName());*/

	PlayerRef = static_cast<AUnrealFPTeam01Character*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerRef->isFP && !isActive && !isInHand)
	{
		if(PlayerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, UnderMouseHit))
		{
			if(UnderMouseHit.Actor->IsA(APlateauInteractable::StaticClass()))
			{
				this->SetActorLocation(UnderMouseHit.Location);
				SetGreenPlacement();
			}
		}
	}
}

void ATowerBase::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetMeshMaterials();
	isActive = true;
	PlayerRef->ApplyConstruction();
}

bool ATowerBase::CheckHit()
{
	FVector sphereOrigin = this->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objectsTypeToQuerry;
	//objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_EngineTraceChannel4));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	bool bHasHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereOrigin, TowerRangeRadius, objectsTypeToQuerry, nullptr, actorsToIgnore, ActorsHit);

	DrawDebugSphere(GetWorld(), sphereOrigin, TowerRangeRadius, 40, FColor(255, 0, 0));

	return bHasHit;
}

void ATowerBase::TowerTakeDamage(int damage)
{
	TowerHealth -= damage;
}

void ATowerBase::DestroyTower()
{
	Destroy();
}

void ATowerBase::SetGreenPlacement()
{
	for(int i = 0; i < BaseMeshMaterial.Num(); i++)
	{
		MeshComponent->SetMaterial(i, GreenMaterial);
	}

	isActive = false;
}

void ATowerBase::SetBluePlacement()
{
	for (int i = 0; i <BaseMeshMaterial.Num(); i++)
	{
		MeshComponent->SetMaterial(i, BlueMaterial);
	}

	isActive = false;
}

void ATowerBase::SetMeshMaterials()
{
	for (int i = 0; i < BaseMeshMaterial.Num(); i++)
	{
		MeshComponent->SetMaterial(i, BaseMeshMaterial[i]);
	}

	isActive = true;
}


AActor* ATowerBase::FindTarget(TArray<AActor*>& ActorsArray)
{
	AActor* Target = ActorsArray[0];
	FVector closestTarget = Target->GetActorLocation();
	if (ActorsArray.Num() != 0)
	{
		for (int i = 0; i < ActorsArray.Num(); i++)
		{
			FVector Distance1 = ActorsArray[i]->GetActorLocation() - EndPathActor->GetActorLocation();
			FVector Distance2 = closestTarget - EndPathActor->GetActorLocation();

			if (Distance1.Size() <= Distance2.Size())
			{
				Target = ActorsArray[i];
				closestTarget = Target->GetActorLocation();
			}
		}
	} else
	{
		GLog->Log(FString::FromInt(ActorsArray.Num()));
	}
	return Target;
}

void ATowerBase::RotateTowardTarget(AActor* target)
{
	FRotator RotationToRotate = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target->GetActorLocation());
	FRotator newRotation = { 0.f, RotationToRotate.Yaw, 0.f };
	this->SetActorRotation(newRotation);
}

void ATowerBase::InitializeTower()
{
	isActive = false;
	if(!isActive)
	{
		MeshComponent->SetCollisionProfileName(TEXT("NoCollisionC"));
	}

}

