// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LunarticGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API ULunarticGameInstance : public UGameInstance
{
	GENERATED_BODY()

	ULunarticGameInstance();

public:

	UFUNCTION()
	void LevelUp();

	UFUNCTION()
	int GetLevel();

private:
	int Level;
};
