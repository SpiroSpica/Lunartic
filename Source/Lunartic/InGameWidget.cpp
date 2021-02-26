// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

void UInGameWidget::SetKillCount(int _Count)
{
	FString tmp = FString::Printf(TEXT("Destroyed : %d"), _Count);
	FText Destroyed = FText::FromString(tmp);
	Score->SetText(Destroyed);
	KillCount = _Count;
}

void UInGameWidget::SetHP(int _HP, int _MaxHP)
{
	FString tmp = FString::Printf(TEXT("%d"), _HP);
	FText HPVal = FText::FromString(tmp);
	HPStat->SetText(HPVal);
	
	float percent = (float)_HP / (float)_MaxHP;
	HP = _HP;
	HealthBar->SetPercent(percent);

	UE_LOG(LogTemp, Warning, TEXT("%d %d"), _HP, _MaxHP);
}

void UInGameWidget::SetWeaponStatus(int _WeaponNum, int _CurrentAmmo, int _MaxAmmo)
{
	FString tmp = FString::Printf(TEXT("%d / %d"),  _CurrentAmmo, _MaxAmmo);
	FText Weapon = FText::FromString(tmp);
	AmmoStat->SetText(Weapon);

	FString tmp2;
	switch (_WeaponNum)
	{
	case 0:
		tmp2 = FString::Printf(TEXT("Projectile"));
		break;
	case 1:
		tmp2 = FString::Printf(TEXT("MACHINE GUN"));
		break;
	case 2:
		tmp2 = FString::Printf(TEXT("GERNADE"));
		break;
	case 3:
		tmp2 = FString::Printf(TEXT("SHOTGUN"));
		break;
	}
	WeaponStat->SetText(FText::FromString(tmp2));
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
	UGameplayStatics::OpenLevel(this,"LunarticStage");

}

void UInGameWidget::RetryThisLevel()
{
	UGameplayStatics::OpenLevel(this, "LunarticStage");
}

void UInGameWidget::BackToMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
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