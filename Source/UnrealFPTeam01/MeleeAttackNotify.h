// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPTEAM01_API UMeleeAttackNotify : public UAnimNotify {
	GENERATED_BODY()
	
public:

	UMeleeAttackNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
