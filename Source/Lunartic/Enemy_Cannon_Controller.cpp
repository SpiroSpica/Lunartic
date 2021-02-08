// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Cannon_Controller.h"

AEnemy_Cannon_Controller::AEnemy_Cannon_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBData(TEXT("BlackboardData'/Game/Enemy/Cannon/Enemy_Cannon_BB.Enemy_Cannon_BB'"));
	if (BBData.Succeeded())
	{
		BBAsset = BBData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTData(TEXT("BehaviorTree'/Game/Enemy/Cannon/Enemy_Cannon_BT.Enemy_Cannon_BT'"));
	if (BTData.Succeeded())
	{
		BTAsset = BTData.Object;
	}
}