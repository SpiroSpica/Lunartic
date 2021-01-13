// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticGameMode.h"
#include "LunarticPlayerController.h"
#include "LunarticCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALunarticGameMode::ALunarticGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALunarticPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}