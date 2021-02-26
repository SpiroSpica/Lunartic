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
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "DrawDebugHelpers.h"
#include "LunarticGameInstance.h"
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

	//damage dealt to the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	//time between each shoot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootInterval;

	//maximum number of ammo possible. gun will be reloaded to this number after reload
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo;

	//time required to reload
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadInterval;

	//1 = projectile, 2 = hitscan, 3 = artilery projectile, 4 = shotgun
	uint8 WeaponStyle;
};



UCLASS()
class ALunarticPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALunarticPlayerController();

	class UInGameWidget* GetHud() const;
	ULunarticGameInstance* GameInstance;

protected:

	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	

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

	UPROPERTY()
	int CharacterHP;

	UPROPERTY()
	int CharacterMaxHP;

public:

	//player movement function
	UFUNCTION()
	void UpDown(float NewAxisValue);
	UFUNCTION()
	void LeftRight(float NewAxisValue);

	//player shooting function
	UFUNCTION()
	void Shoot();
	UFUNCTION()
	void ShootExplosive();
	UFUNCTION()
	void HitScan();
	UFUNCTION()
	void Shotgun();

	//Shooting handle mechanism
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
	void Reload();
	UFUNCTION()
	void ReloadWeapon();

	UFUNCTION()
	void OnEnemyKill(int Num);

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void FailGame();

	UPROPERTY(VisibleAnyWhere)
	bool SpecialWeaponFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle GameEndTimerHandle;

	UPROPERTY(VisibleAnyWhere)
	bool ReloadFlag;

	UPROPERTY(VisibleAnyWhere)
	bool GameEndFlag;

	UPROPERTY(VisibleAnyWhere)
	int WeaponType;

	UPROPERTY(VisibleAnyWhere)
	int KillCount;

	UPROPERTY(VisibleAnywhere)
	int RequiredKill;

};

