// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Castle.generated.h"

UCLASS()
class UNREALFPTEAM01_API ACastle : public AActor
{
	GENERATED_BODY()
	
public:	
	ACastle();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float maxHealth;

	UFUNCTION()
	void ApplyDamage(float damage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCastleDestroyed();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
