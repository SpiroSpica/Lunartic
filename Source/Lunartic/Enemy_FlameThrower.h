// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "LunarticMonster.h"
#include "LunarticCharacter.h"
#include "Enemy_FlameThrower_Controller.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Enemy_FlameThrower.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS(Blueprintable)
class LUNARTIC_API AEnemy_FlameThrower : public ALunarticMonster
{
	GENERATED_BODY()

public:
	AEnemy_FlameThrower();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	ALunarticCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere, Category = Visual)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* Flame1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* Flame2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* BottomFire;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* BackFire1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* BackFire2;
	
	UPROPERTY(VisibleAnywhere)
	bool OnAttack;

	FOnAttackEndDelegate OnAttackEnd;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
	bool AttackAvailable();

	UFUNCTION()
	void FlameDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle FlameThrowerTimerHandle;

	UFUNCTION()
	void Attack();
};