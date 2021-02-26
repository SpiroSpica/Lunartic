// Fill out your copyright notice in the Description page of Project Settings.


#include "LunarticGameInstance.h"

ULunarticGameInstance::ULunarticGameInstance()
{
	Level = 0;

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void ULunarticGameInstance::LevelUp()
{
	Level++;
}

int ULunarticGameInstance::GetLevel()
{
	return Level;
}