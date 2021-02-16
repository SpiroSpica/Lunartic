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

	UPROPERTY()
	int EnemyCount;
	UPROPERTY()
	int RequiredKill;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int HP;
	
	UFUNCTION()
	void OnEnemyKill();

	UFUNCTION()
	void OnTakeDamage(int Damage);

	UFUNCTION()
	int GetHP();

	UFUNCTION()
	int GetKillCount();

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

	UPROPERTY()
	float PastRotationYaw;

	UFUNCTION()
	void FireEffect(bool firing);

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
	
	
};

