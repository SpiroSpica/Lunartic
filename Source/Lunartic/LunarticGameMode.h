// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InGameWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LunarticGameMode.generated.h"

UCLASS(minimalapi)
class ALunarticGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALunarticGameMode();

	UFUNCTION()
	void StageClear(bool Clear);

	UFUNCTION()
	bool isStageCleared();

	UFUNCTION()
	bool isSucceeded();

private:
	UPROPERTY(VisibleAnywhere)
	bool ClearFlag;

	UPROPERTY(VisibleAnywhere)
	bool FailFlag;


	UPROPERTY()
	FTimerHandle PauseTimer;

};



