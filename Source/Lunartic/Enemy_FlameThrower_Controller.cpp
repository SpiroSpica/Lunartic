// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_FlameThrower_Controller.h"

AEnemy_FlameThrower_Controller::AEnemy_FlameThrower_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBData(TEXT("BlackboardData'/Game/Enemy/FlameThrower/Enemy_FlameThrower_BB.Enemy_FlameThrower_BB'"));
	if (BBData.Succeeded())
	{
		BBAsset = BBData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTData(TEXT("BehaviorTree'/Game/Enemy/FlameThrower/Enemy_FlameThrower_BT.Enemy_FlameThrower_BT'"));
	if (BTData.Succeeded())
	{
		BTAsset = BTData.Object;
	}
}