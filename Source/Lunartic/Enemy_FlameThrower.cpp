// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_FlameThrower.h"

AEnemy_FlameThrower::AEnemy_FlameThrower()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(150.0f);
	Capsule->SetCapsuleRadius(70.0f);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

}

void AEnemy_FlameThrower::BeginPlay()
{
	Super::BeginPlay();

	TargetCharacter = Cast<ALunarticCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}