// Fill out your copyright notice in the Description page of Project Settings.




#include "LunarticMonsterController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ALunarticMonsterController::ALunarticMonsterController()
{
	RepeatInterval = 0.1f;
}

void ALunarticMonsterController::BeginPlay()
{
	Super::BeginPlay();	
}

void ALunarticMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ALunarticMonsterController::OnRepeatTimer, RepeatInterval, true);
}

void ALunarticMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void ALunarticMonsterController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	ACharacter* const MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
	{
		return;
	}

	FNavLocation NextLocation;
	
	FVector Destination = MyCharacter->GetActorLocation();

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	

}