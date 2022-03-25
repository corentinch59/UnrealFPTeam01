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

	TowerHealthOnRoad = 100;
	TowerDamageOnRoad = 1;
	TowerRangeRadiusOnRoad = 250.f;
	TowerAttackRateOnRoad = 1.f;

	TowerHealthOnSide = 100;
	TowerDamageOnSide = 1;
	TowerRangeRadiusOnSide = 250.f;
	TowerAttackRateOnSide = 1.f;

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

	if(MeshComponent->GetNumMaterials() > 0)
	{
		for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
		{
			BaseMeshMaterial.Add(MeshComponent->GetMaterial(i));
		}
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
			if(UnderMouseHit.Actor->ActorHasTag(TEXT("Road")))
			{
				this->SetActorLocation(UnderMouseHit.Location);
				SetBluePlacement();
			}
			if(UnderMouseHit.Actor->ActorHasTag(TEXT("Side")))
			{
				this->SetActorLocation(UnderMouseHit.Location);
				SetGreenPlacement();
			}
		}
	}
}

void ATowerBase::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (MeshComponent->GetNumMaterials() > 0)
	{
		SetMeshMaterials();
	}
	isActive = true;
	PlayerRef->ApplyConstruction();

	GLog->Log("Clicked");
}

bool ATowerBase::CheckHit()
{
	FVector sphereOrigin = this->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objectsTypeToQuerry;
	objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_EngineTraceChannel4));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	bool bHasHit;
	switch (TowerState)
	{
	case OnSide:
		bHasHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereOrigin, TowerRangeRadiusOnSide, objectsTypeToQuerry, nullptr, actorsToIgnore, ActorsHit);
		break;
	default:
		bHasHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereOrigin, TowerRangeRadiusOnSide, objectsTypeToQuerry, nullptr, actorsToIgnore, ActorsHit);
		break;
	}

	DrawDebugSphere(GetWorld(), sphereOrigin, TowerRangeRadiusOnRoad, 40, FColor(255, 0, 0));

	return bHasHit;
}

void ATowerBase::TowerTakeDamage(int damage)
{
	switch (TowerState)
	{
	case OnSide:
		TowerHealthOnSide -= damage;
		break;
	default:
		TowerHealthOnRoad -= damage;
		break;
	}
}

void ATowerBase::DestroyTower()
{
	Destroy();
}

void ATowerBase::SetGreenPlacement()
{
	if (MeshComponent->GetNumMaterials() > 0)
	{
		for (int i = 0; i < BaseMeshMaterial.Num(); i++)
		{
			MeshComponent->SetMaterial(i, GreenMaterial);
		}
	}

	isActive = false;
	TowerState = OnSide;
}

void ATowerBase::SetBluePlacement()
{
	if (MeshComponent->GetNumMaterials() > 0)
	{
		for (int i = 0; i <BaseMeshMaterial.Num(); i++)
		{
			MeshComponent->SetMaterial(i, BlueMaterial);
		}
	}

	isActive = false;
	TowerState = OnRoad;
}

void ATowerBase::SetMeshMaterials()
{
	if (MeshComponent->GetNumMaterials() > 0)
	{
		for (int i = 0; i < BaseMeshMaterial.Num(); i++)
		{
			MeshComponent->SetMaterial(i, BaseMeshMaterial[i]);
		}
	}

	isActive = true;
}


AActor* ATowerBase::FindTarget(TArray<AActor*>& ActorsArray, TArray<AActor*>& TargetsToIgnore)
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
				if (TargetsToIgnore.Num() > 0 && ActorsHit.Num() < 0)
				{
					for(int j = 0; j < TargetsToIgnore.Num(); j++)
					{
						if(ActorsArray[i] != TargetsToIgnore[j])
						{
							Target = ActorsArray[i];
							closestTarget = Target->GetActorLocation();
						}
					}
				} else
				{
					Target = ActorsArray[i];
					closestTarget = Target->GetActorLocation();
				}
			}
		}
	} else
	{
		GLog->Log(FString::FromInt(ActorsArray.Num()));
	}
	TargetsToIgnore.Add(Target);
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

