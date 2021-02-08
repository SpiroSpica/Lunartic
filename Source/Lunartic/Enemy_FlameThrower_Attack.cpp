// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_FlameThrower.h"
#include "LunarticMonsterController.h"
#include "Enemy_FlameThrower_Attack.h"

UEnemy_FlameThrower_Attack::UEnemy_FlameThrower_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UEnemy_FlameThrower_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = UBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_FlameThrower* Chara = Cast<AEnemy_FlameThrower>(OwnerComp.GetAIOwner()->GetPawn());

	if (Chara == nullptr)
	{
		EBTNodeResult::Failed;
	}

	if (Chara->AttackAvailable())
	{
		IsAttacking = true;
		Chara->Attack();

		Chara->OnAttackEnd.AddLambda([this]()->void {
			IsAttacking = false;
			});
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::InProgress;
}

void UEnemy_FlameThrower_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBTTaskNode::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}