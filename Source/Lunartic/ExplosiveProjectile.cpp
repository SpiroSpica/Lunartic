// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveProjectile.h"
#include "DrawDebugHelpers.h"

void AExplosiveProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());

	FVector ExplosionLocation = Hit.GetActor()->GetActorLocation();

	// Set what actors to seek out from it's collision channel
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	// Ignore any specific actors
	TArray<AActor*> ignoreActors;
	// Ignore self or remove this line to not ignore any
	ignoreActors.Init(this, 1);

	// Array of actors that are inside the radius of the sphere
	TArray<AActor*> outActors;

	// Total radius of the sphere
	float radius = 300.0f;

	// Class that the sphere should hit against and include in the outActors array (Can be null)
	UClass* seekClass = ALunarticMonster::StaticClass(); // NULL;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), ExplosionLocation, radius, traceObjectTypes, seekClass, ignoreActors, outActors);

	
	// Optional: Use to have a visual representation of the SphereOverlapActors
	DrawDebugSphere(GetWorld(), ExplosionLocation, radius, 12, FColor::Red, true, 10.0f);

	for (AActor* overlappedActor : outActors)
	{
		ALunarticMonster* Monster = Cast<ALunarticMonster>(overlappedActor);

		Monster->OnTakeDamage(100);

		Monster->MeshComp->AddRadialImpulse(ExplosionLocation, radius, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
		Monster->MeshComp->AddRadialForce(ExplosionLocation, radius, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
		//UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Explosive"));
	SetLifeSpan(0.01f);

}