// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "InGameWidget.generated.h"

/**
 * 
 */

UCLASS()
class LUNARTIC_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HPStat;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WeaponStat;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ReloadText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* NextLevelScreen;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* NextLevelButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CancelButton;

	UFUNCTION()
	void SetKillCount(int _Count);

	UFUNCTION()
	void SetHP(int _HP);

	UFUNCTION()
	void SetWeaponStatus(int _WeaponNum, int _CurrentAmmo, int _MaxAmmo);

	UFUNCTION()
	void ReloadAlarm(bool Switch);

	UFUNCTION()
	void BlurScreen(bool Switch);

	UFUNCTION()
	void SendToNextLevel();

	UFUNCTION()
	void BackToMenu();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY()
	int KillCount;

	UPROPERTY()
	int HP;

	UPROPERTY()
	int WeaponNum;

	UPROPERTY()
	int CurrentAmmo;

	UPROPERTY()
	int MaxAmmo;

};
