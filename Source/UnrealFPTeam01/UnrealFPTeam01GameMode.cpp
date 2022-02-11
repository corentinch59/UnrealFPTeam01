// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealFPTeam01GameMode.h"
#include "UnrealFPTeam01HUD.h"
#include "UnrealFPTeam01Character.h"
#include "UObject/ConstructorHelpers.h"

AUnrealFPTeam01GameMode::AUnrealFPTeam01GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AUnrealFPTeam01HUD::StaticClass();
}
