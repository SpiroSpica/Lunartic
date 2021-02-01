// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "Animation/AnimInstance.h"
#include "Enemy_Cannon_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API UEnemy_Cannon_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemy_Cannon_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
};
