// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AProjectile.h"
#include "DrawDebugHelpers.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class LUNARTIC_API AExplosiveProjectile : public AAProjectile
{
	GENERATED_BODY()
	

		
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
