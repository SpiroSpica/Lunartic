// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lunartic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "LunarticCharacter.h"
#include "LunarticMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Enemy_Cannon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS(Blueprintable)
class LUNARTIC_API AEnemy_Cannon : public ALunarticMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Cannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	ALunarticCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere, Category = Visual)
	USkeletalMeshComponent* Cannon;
	
	UPROPERTY(EditAnywhere, Category = Visual)
	USkeletalMeshComponent* Base;
	
	UPROPERTY(EditAnywhere, Category = Visual)
	USkeletalMeshComponent* Legs;

	UPROPERTY(EditAnywhere, Category = Visual)
	UNiagaraSystem* Explosion;

	UPROPERTY(VisibleAnywhere)
	bool OnAttack;
	

	FOnAttackEndDelegate OnAttackEnd;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	FVector FirePlace;

	UFUNCTION()
	void Attack();

	UFUNCTION()
	bool AttackAvailable();

	UFUNCTION()
	void Fire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
