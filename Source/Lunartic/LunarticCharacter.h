// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LunarticGameMode.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "GameFramework/SpringArmComponent.h"
#include "LunarticCharacter.generated.h"


UCLASS(Blueprintable)
class ALunarticCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALunarticCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/* major appearance of character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Outfit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* HoverFL;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* HoverFR;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* HoverBL;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* HoverBR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* HoverSmoke;

	/* De/Activate Niagra Effect (Shooting) */
	UFUNCTION()
	void FireEffect(bool firing);
	
	/* Calculate Enemy Kill Count by character*/
	UFUNCTION()
	void OnEnemyKill();

	/* Calculate HP when damaged, HP cannot be below 0 */
	UFUNCTION()
	void OnTakeDamage(int Damage);

	/* Return HP of character int value */
	UFUNCTION()
	int GetHP();

	/* Return HP of character int value */
	UFUNCTION()
	int GetMaxHP();


	/* Return enemy kill count int value */
	UFUNCTION()
	int GetKillCount();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxHP;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	
	/* counts number of enemies killed*/
	UPROPERTY()
	int EnemyCount;
	/* number of enemies required to kill to move to next stage*/
	UPROPERTY()
	int RequiredKill;
	/* float used to check the direction of character rotates */
	UPROPERTY()
	float PastRotationYaw;
	
};

