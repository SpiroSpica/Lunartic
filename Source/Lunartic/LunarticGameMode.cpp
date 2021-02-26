// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticGameMode.h"
#include "LunarticPlayerController.h"
#include "LunarticCharacter.h"
#include "MonsterSpawner.h"

#include "UObject/ConstructorHelpers.h"

ALunarticGameMode::ALunarticGameMode()
{
	ClearFlag = false;
	FailFlag = false;
	// use our custom PlayerController class
	PlayerControllerClass = ALunarticPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/PlayerCharacter'"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}


void ALunarticGameMode::StageClear(bool Clear)
{
	ClearFlag = true;
	FailFlag = Clear;
}

bool ALunarticGameMode::isStageCleared()
{
	return ClearFlag;
}

bool ALunarticGameMode::isSucceeded()
{
	return FailFlag;
}