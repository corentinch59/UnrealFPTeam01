// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UnrealFPTeam01HUD.generated.h"

UCLASS()
class AUnrealFPTeam01HUD : public AHUD
{
	GENERATED_BODY()

public:
	AUnrealFPTeam01HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

