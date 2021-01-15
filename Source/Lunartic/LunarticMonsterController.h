// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "AIController.h"
#include "LunarticMonster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LunarticMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API ALunarticMonsterController : public AAIController
{
	GENERATED_BODY()

	

public:
	ALunarticMonsterController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();
	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;

};
