// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionProfileName(TEXT("Custom"));
	MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel3);

	RootComponent = MeshComponent;

	ProjectileOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileOrigin"));
	ProjectileOrigin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	ProjectileOrigin->SetRelativeLocation(FVector(0.f, 0.f, 50.f));


	TowerHealth = 100;
	TowerDamage = 1;
	TowerRangeRadius = 250.f;
	TowerAttackRate = 1.f;
	TagOfEndPath = "EndPath";
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

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
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATowerBase::CheckHit()
{
	FVector sphereOrigin = this->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objectsTypeToQuerry;
	objectsTypeToQuerry.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
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

AActor* ATowerBase::FindTarget(TArray<AActor*>& ActorsArray)
{
	AActor* Target = ActorsArray[0];
	FVector closestTarget = Target->GetActorLocation();
	FVector test = EndPathActor->GetActorLocation();
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

// Called to bind functionality to input
void ATowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

