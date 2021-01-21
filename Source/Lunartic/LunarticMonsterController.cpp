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
		BBAsset = BBData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTData(TEXT("'/Game/EnemyBT.EnemyBT'"));
	if (BTData.Succeeded())
	{
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

	if (UseBlackboard(BBAsset, Blackboard))
	{
		ACharacter* const MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (MyCharacter == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Character Failed"));
		}
		else
		{
			Blackboard->SetValueAsObject(TargetKey, MyCharacter);
		}
		
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("Running AIController Monster Behavior Tree Failed"));
		}
	}

}

void ALunarticMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}