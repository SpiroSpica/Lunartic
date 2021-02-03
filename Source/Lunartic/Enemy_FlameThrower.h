// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LunarticMonster.h"
#include "LunarticCharacter.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_FlameThrower.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API AEnemy_FlameThrower : public ALunarticMonster
{
	GENERATED_BODY()

public:
	AEnemy_FlameThrower();

protected:
	virtual void BeginPlay() override;

public:

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
	
};
