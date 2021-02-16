// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy_FlameThrower_Attack.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API UEnemy_FlameThrower_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UEnemy_FlameThrower_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	bool IsAttacking = false;
};
