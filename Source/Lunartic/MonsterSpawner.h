// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "LunarticMonster.h"
#include "LunarticGameMode.h"
#include "LunarticGameInstance.h"
#include "Math/UnrealMathUtility.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class LUNARTIC_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	UPROPERTY()
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY()
	UParticleSystemComponent* SpawnPoint;

	UPROPERTY()
	TArray<ALunarticMonster*> UnitSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> UnitToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* UnitFlame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* UnitCannon;

	UPROPERTY()
	float SpawnInterval;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	bool isGameRunning;

	UFUNCTION()
	void SpawnUnit();

	UFUNCTION()
	void StageClear(bool Succeeded);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int StageLevel;
	ULunarticGameInstance* GameInstance;

};
