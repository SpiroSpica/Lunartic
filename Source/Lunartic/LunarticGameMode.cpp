// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticGameMode.h"
#include "LunarticPlayerController.h"
#include "LunarticCharacter.h"
#include "MonsterSpawner.h"
#include "UObject/ConstructorHelpers.h"

ALunarticGameMode::ALunarticGameMode()
{
	ClearFlag = false;
	// use our custom PlayerController class
	PlayerControllerClass = ALunarticPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ALunarticGameMode::StageClear()
{
	ClearFlag = true;
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Should be paused"));
	}
}

bool ALunarticGameMode::isStageCleared()
{
	return ClearFlag;
}