// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
	class UTextBlock* NextStage;

protected:

	virtual void NativeConstruct() override;

	
};
