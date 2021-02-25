// Fill out your copyright notice in the Description page of Project Settings.


#include "LunarticMonster.h"
#include "LunarticMonsterController.h"

// Sets default values
ALunarticMonster::ALunarticMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyCharacter = Cast<ALunarticCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	DeathMotion = CreateDefaultSubobject<UNiagaraSystem>(TEXT("DeathEffect"));
	
}

// Called when the game starts or when spawned
void ALunarticMonster::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Enemy");
}

/* Decrease HP When damage taken*/
void ALunarticMonster::OnTakeDamage(int Damage)
{
	HP -= Damage;

	/* if HP goes below 0, tell character to increase kill count and destroy actor itself */
	if (HP <= 0)
	{
		MyCharacter->OnEnemyKill();
		this->Die();
	}
}


void ALunarticMonster::Die()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathMotion, this->GetActorLocation(), this->GetActorRotation());
	this->Destroy();
}