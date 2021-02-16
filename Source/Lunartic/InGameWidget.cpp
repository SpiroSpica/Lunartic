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
		tmp = "RELOADING"; 
	}
	else
	{
		tmp = "";
	}

	FText ReloadAlarmText = FText::FromString(tmp);
	ReloadText->SetText(ReloadAlarmText);

}

void UInGameWidget::BlurScreen(bool Switch)
{
	if (Switch)
	{
		NextLevelScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NextLevelScreen->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UInGameWidget::FailedScreen(bool Switch)
{
	if (Switch)
	{
		FailLevelScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		FailLevelScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInGameWidget::SendToNextLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Send to next level"));
	GameInstance->LevelUp();
	UGameplayStatics::OpenLevel(this,"TopDownExampleMap");

}

void UInGameWidget::RetryThisLevel()
{
	UGameplayStatics::OpenLevel(this, "TopDownExampleMap");
}

void UInGameWidget::BackToMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("BackToMenu"));
}

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NextLevelScreen->SetVisibility(ESlateVisibility::Hidden);
	FailLevelScreen->SetVisibility(ESlateVisibility::Hidden);

	if (!NextLevelButton->OnClicked.IsBound())
	{
		NextLevelButton->OnClicked.AddDynamic(this, &UInGameWidget::SendToNextLevel);
	}
	if (!CancelButton->OnClicked.IsBound())
	{
		CancelButton->OnClicked.AddDynamic(this, &UInGameWidget::BackToMenu);
	}
	if (!RetryButton->OnClicked.IsBound())
	{
		RetryButton->OnClicked.AddDynamic(this, &UInGameWidget::RetryThisLevel);
	}
	if (!ExitButton->OnClicked.IsBound())
	{
		ExitButton->OnClicked.AddDynamic(this, &UInGameWidget::BackToMenu);
	}

	GameInstance =  Cast<ULunarticGameInstance>(GetGameInstance());
	
	FString tmp = FString::Printf(TEXT("Stage %d"), GameInstance->GetLevel());
	FText StageLV = FText::FromString(tmp);
	StageLevel->SetText(StageLV);
}