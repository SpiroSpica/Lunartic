// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Lunartic.h"
#include "MonsterBTDecoratorIsInRange.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API UMonsterBTDecoratorIsInRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UMonsterBTDecoratorIsInRange();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Distance;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) const override;
};
