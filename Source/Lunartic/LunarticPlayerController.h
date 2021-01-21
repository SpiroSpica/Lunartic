// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AProjectile.h"
#include "ExplosiveProjectile.h"
#include "LunarticMonster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "LunarticPlayerController.generated.h"


UCLASS()
class ALunarticPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALunarticPlayerController();

protected:

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAProjectile> ProjectileClass;

	UPROPERTY()
	bool isFire;

	UPROPERTY()
	bool notShooting;

	

public:

	UFUNCTION()
	void UpDown(float NewAxisValue);
	UFUNCTION()
	void LeftRight(float NewAxisValue);

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void ShootExplosive();
	
	UFUNCTION()
	void HitScan();
		
	UFUNCTION()
	void StartShoot();

	UFUNCTION()
	void EndShoot();

	UFUNCTION()
	void WeaponChange(int num);

	UFUNCTION()
	void AttackLimit();

	UFUNCTION()
	void Bomb();

	UPROPERTY(VisibleAnyWhere)
	bool SpecialWeaponFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle MemberTimerHandle;

	UPROPERTY(VisibleAnyWhere)
	int WeaponType;
};


