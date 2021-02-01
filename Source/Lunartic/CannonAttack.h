// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CannonAttack.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API UCannonAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCannonAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;
};
