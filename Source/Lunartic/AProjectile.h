// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LunarticMonster.h"
#include "AProjectile.generated.h"

UCLASS()
class LUNARTIC_API AAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	/* Set direction of projectile */
	UFUNCTION()
	void FireInDirection(const FVector& ShootDireciton);

	/* Set event when projectile collide with other thing*/
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	/* Set Damage that projectile can give */
	UFUNCTION()
	void SetDamage(int Dmg);

private:

	/* 
	Component that forms projectile
		CollisionComponent : Collide
		ProjectileMovementComponent : Controls projectile movement
		ProjectileMeshComponent : Mesh Component for projectile appearance
		ProjectileMaterialInstance : Material for mesh 
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	/* Damage that projectile can give */
	UPROPERTY(VisibleAnywhere)
	int Damage;
};
