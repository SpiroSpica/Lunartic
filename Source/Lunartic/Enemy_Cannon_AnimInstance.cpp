// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Cannon_AnimInstance.h"

UEnemy_Cannon_AnimInstance::UEnemy_Cannon_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UEnemy_Cannon_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}