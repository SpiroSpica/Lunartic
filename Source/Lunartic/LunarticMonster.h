// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "LunarticMonster.generated.h"

UCLASS(Blueprintable)
class ALunarticMonster : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALunarticMonster();

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	UPROPERTY(EditAnyWhere, Category = Visual)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnyWhere, Category = Stat)
	int HP;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	UCapsuleComponent* Capsule;

	UFUNCTION()
	void OnTakeDamage(int Damage);

};