// Fill out your copyright notice in the Description page of Project Settings.




#include "LunarticMonsterController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName ALunarticMonsterController::TargetKey(TEXT("Target"));
const FName ALunarticMonsterController::HomePosKey(TEXT("HomePos"));

ALunarticMonsterController::ALunarticMonsterController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBData(TEXT("'/Game/EnemyBB.EnemyBB'"));
	if (BBData.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("BB Succeeded"));
		BBAsset = BBData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTData(TEXT("'/Game/EnemyBT.EnemyBT'"));
	if (BTData.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("BT Succeeded"));
		BTAsset = BTData.Object;
	}
	RepeatInterval = 0.1f;
}

void ALunarticMonsterController::BeginPlay()
{
	Super::BeginPlay();	
}

void ALunarticMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess Succeeded"));

	if (UseBlackboard(BBAsset, Blackboard))
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard usage Succeeded"));
		ACharacter* const MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (MyCharacter == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Character Failed"));
		}
		else
		{
			Blackboard->SetValueAsObject(TargetKey, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
		
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("Running AIController Monster Behavior Tree Failed"));
		}
	}
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ALunarticMonsterController::OnRepeatTimer, RepeatInterval, true);
}

void ALunarticMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
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