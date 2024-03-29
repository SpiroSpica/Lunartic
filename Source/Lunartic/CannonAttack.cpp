// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonAttack.h"
#include "Enemy_Cannon_Controller.h"
#include "Enemy_Cannon.h"

UCannonAttack::UCannonAttack()
{
	bNotifyTick = true;

	/* flag to know if cannon's attack procedure has started or not */
	IsAttacking = false;
}

EBTNodeResult::Type UCannonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = UBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_Cannon* Chara = Cast<AEnemy_Cannon>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Chara == nullptr)
	{
		EBTNodeResult::Failed;
	}

	/* If Cannon can attack, initiate attack procedure with flag on. Add broadcast that catches the end of attack procedrue*/
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

void UCannonAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBTTaskNode::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	/* if flag turned off after the attack, tells behavior tree that the procedure has ended*/
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}