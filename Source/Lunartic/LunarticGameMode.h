// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InGameWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/WidgetComponent.h"
#include "LunarticGameMode.generated.h"

UCLASS(minimalapi)
class ALunarticGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALunarticGameMode();

	UFUNCTION()
	void StageClear();

	UFUNCTION()
	bool isStageCleared();

	UFUNCTION()
	void PauseGame();

	UPROPERTY(VisibleAnywhere)
	bool ClearFlag;

	UPROPERTY()
	FTimerHandle PauseTimer;

};



