// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AProjectile.h"
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
	// End PlayerController interface

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAProjectile> ProjectileClass;



	

public:

	UFUNCTION()
	void UpDown(float NewAxisValue);
	UFUNCTION()
	void LeftRight(float NewAxisValue);

	UFUNCTION()
	void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;


};


