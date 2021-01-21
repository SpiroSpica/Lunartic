// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBTDecoratorIsInRange.h"
#include "LunarticMonsterController.h"
#include "LunarticMonster.h"
#include "BehaviorTree/BlackboardComponent.h"


UMonsterBTDecoratorIsInRange::UMonsterBTDecoratorIsInRange()
{
	NodeName = TEXT("CanAttack");
	UE_LOG(LogTemp, Warning, TEXT("Generated"));
}

bool UMonsterBTDecoratorIsInRange::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CalcDist1"));
		return false;
	}

	auto Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ALunarticMonsterController::TargetKey));
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CalcDist2"));
		return false;
	}

	bResult = Target->GetDistanceTo(ControllingPawn) <= 400.0f;

	if (bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackAllowed"));
	}
	return bResult;
	
}