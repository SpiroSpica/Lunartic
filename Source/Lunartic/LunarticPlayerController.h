// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AProjectile.h"
#include "Explosive.h"
#include "LunarticMonster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LunarticCharacter.h"
#include "InGameWidget.h"
#include "DrawDebugHelpers.h"
#include "LunarticPlayerController.generated.h"


UENUM(BlueprintType)
enum class WeaponType : uint8
{
	Projectile = 0 UMETA(DisplayName = "Projectile"),
	HitScan UMETA(DisplayName = "HitScan"),
};


USTRUCT(Atomic, BlueprintType)
struct FWeaponStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadInterval;

	uint8 WeaponStyle;
};



UCLASS()
class ALunarticPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALunarticPlayerController();

	class UInGameWidget* GetHud() const;

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

	UPROPERTY()
	TArray<float> ShootReload;	

	UPROPERTY()
	TArray<FWeaponStatus> Weapon;

	UPROPERTY()
	float ShootCooltime;

	UPROPERTY()
	ALunarticCharacter* MyCharacter;

	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, Category = UI)
	TSubclassOf<class UInGameWidget> HudClass;


private:

	UPROPERTY()
	class UInGameWidget* Hud;

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

	UFUNCTION()
	void Shotgun();

	UPROPERTY(VisibleAnyWhere)
	bool SpecialWeaponFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle MemberTimerHandle;

	UPROPERTY(VisibleAnyWhere)
	int WeaponType;



};

