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
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/PlayerCharacter'"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}


void ALunarticGameMode::StageClear()
{
	ClearFlag = true;
	GetWorld()->GetTimerManager().SetTimer(PauseTimer, this, &ALunarticGameMode::PauseGame, 2.0f, false);
}

bool ALunarticGameMode::isStageCleared()
{
	return ClearFlag;
}

void ALunarticGameMode::PauseGame()
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(true);

		UE_LOG(LogTemp, Warning, TEXT("Should be paused"));
	}
}