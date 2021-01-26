// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

	UPROPERTY(VisibleAnywhere)
	bool ClearFlag;
};



