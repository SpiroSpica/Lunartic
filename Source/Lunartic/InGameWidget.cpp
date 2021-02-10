// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

void UInGameWidget::SetKillCount(int _Count)
{
	FString tmp = FString::Printf(TEXT("Destroyed : %d"), _Count);
	FText Destroyed = FText::FromString(tmp);
	Score->SetText(Destroyed);
	KillCount = _Count;
}

void UInGameWidget::SetHP(int _HP)
{
	FString tmp = FString::Printf(TEXT("HP : %d"), _HP);
	FText HPVal = FText::FromString(tmp);
	HPStat->SetText(HPVal);
	HP = _HP;
}

void UInGameWidget::SetWeaponStatus(int _WeaponNum, int _CurrentAmmo, int _MaxAmmo)
{
	FString tmp = FString::Printf(TEXT("%d : %d / %d"),  _WeaponNum, _CurrentAmmo, _MaxAmmo);
	FText Weapon = FText::FromString(tmp);
	WeaponStat->SetText(Weapon);
	WeaponNum = _WeaponNum;
	CurrentAmmo = _CurrentAmmo;
	MaxAmmo = _MaxAmmo;

}

void UInGameWidget::ReloadAlarm(bool Switch)
{
	FString tmp;
	if (Switch)
	{
		tmp = "";
	}
	else
	{
		tmp = "RELOADING";
	}

	FText ReloadAlarmText = FText::FromString(tmp);
	ReloadText->SetText(ReloadAlarmText);

}

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FText test = FText::FromString("testOngoing");
	NextStage->SetText(test);

	UE_LOG(LogTemp, Warning, TEXT("InGameWidget implemnted"));
}