// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FText test = FText::FromString("testOngoing");
	NextStage->SetText(test);

	UE_LOG(LogTemp, Warning, TEXT("InGameWidget implemnted"));
}