// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticPlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "LunarticCharacter.h"
#include "Engine/World.h"

ALunarticPlayerController::ALunarticPlayerController()
{
	bShowMouseCursor = true;
	isFire = false;
	notShooting = true;
	SpecialWeaponFlag = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	WeaponType = 1;
	ShootCooltime = 1.0f;

	FWeaponStatus tmp1, tmp2, tmp3;
	tmp1.Damage = 10;
	tmp1.ShootInterval = 0.1;
	tmp1.ReloadInterval = 2;
	tmp1.MaxAmmo = 40;
	tmp1.WeaponStyle = 1;
	

	tmp2.Damage = 5;
	tmp2.ShootInterval = 0.03;
	tmp2.ReloadInterval = 5;
	tmp2.MaxAmmo = 200;
	tmp2.WeaponStyle = 2;

	tmp3.Damage = 70;
	tmp3.ShootInterval = 1;
	tmp3.ReloadInterval = 3;
	tmp3.MaxAmmo = 3;
	tmp3.WeaponStyle = 3;

	Weapon.Emplace(tmp1);
	Weapon.Emplace(tmp2);
	Weapon.Emplace(tmp3);
	


	ShootReload = { 0.2f, 0.2f, 1.0f };

}

void ALunarticPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (isFire && notShooting && !SpecialWeaponFlag)
	{
		switch (Weapon[WeaponType].WeaponStyle)
		{
		case 1:
			Shoot();
			break;
		case 2:
			HitScan();
			break;
		case 3:
			ShootExplosive();
			break;
		}
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ALunarticPlayerController::AttackLimit, ShootCooltime, false, Weapon[WeaponType].ShootInterval);
	}
}

void ALunarticPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ALunarticPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ALunarticPlayerController::StartShoot);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ALunarticPlayerController::EndShoot);
	InputComponent->BindAction("SpecialWeapon", IE_Pressed, this, &ALunarticPlayerController::Bomb);
	
	DECLARE_DELEGATE_OneParam(FCustomIntDelegate, const int);
	
	//change weapon type
	InputComponent->BindAction<FCustomIntDelegate>("WeaponChange1", IE_Pressed, this, &ALunarticPlayerController::WeaponChange, 0);
	InputComponent->BindAction<FCustomIntDelegate>("WeaponChange2", IE_Pressed, this, &ALunarticPlayerController::WeaponChange, 1);
	InputComponent->BindAction<FCustomIntDelegate>("WeaponChange3", IE_Pressed, this, &ALunarticPlayerController::WeaponChange, 2);

	
	InputComponent->BindAxis(TEXT("MoveForWard"), this, &ALunarticPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ALunarticPlayerController::LeftRight);
	
}

void ALunarticPlayerController::StartShoot()
{
	if (SpecialWeaponFlag)
	{
		UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
		ALunarticCharacter* MyCharacter = Cast<ALunarticCharacter>(GetCharacter());
		
		FVector ExplosionLocation = MyCharacter->GetCursorToWorld()->GetComponentLocation();

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
			Monster->GetCharacterMovement()->AddRadialImpulse(ExplosionLocation, radius, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
			//UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());
		}
	}
	else
	{
		isFire = true;
	}
}

void ALunarticPlayerController::EndShoot()
{
	isFire = false;
}

void ALunarticPlayerController::Bomb()
{
	ALunarticCharacter* MyCharacter = Cast<ALunarticCharacter>(GetCharacter());
	if (SpecialWeaponFlag == false)
	{
		SpecialWeaponFlag = true;
		MyCharacter->GetCursorToWorld()->SetWorldScale3D(FVector(10, 10, 10));
	}
	else
	{
		SpecialWeaponFlag = false;
		MyCharacter->GetCursorToWorld()->SetWorldScale3D(FVector(1, 1, 1));
	}
}

void ALunarticPlayerController::WeaponChange(int type)
{
	WeaponType = type;
}

void ALunarticPlayerController::UpDown(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		FRotator rot = GetControlRotation();
		FVector Dir = FRotationMatrix(rot).GetScaledAxis(EAxis::X);

		MyCharacter->AddMovementInput(Dir, NewAxisValue);
	}
}

void ALunarticPlayerController::LeftRight(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		FRotator rot = GetControlRotation();
		FVector Dir = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);

		MyCharacter->AddMovementInput(Dir, NewAxisValue);
	}
}

void ALunarticPlayerController::HitScan()
{
	notShooting = false;
	FHitResult target;
	ACharacter* const MyCharacter = GetCharacter();

	FVector start = MyCharacter->GetActorLocation();
	FVector end = start + MyCharacter->GetActorRotation().Vector() * 10000.0f;
	FCollisionQueryParams collisionParams;
	collisionParams.bTraceComplex = true;
	collisionParams.bDebugQuery = true;
	collisionParams.bIgnoreBlocks = false;
	collisionParams.AddIgnoredActor(MyCharacter);
	
	if (MyCharacter->GetWorld()->LineTraceSingleByChannel(target, start, end, ECC_WorldStatic, collisionParams))
	{
		FString targetName;
		target.GetActor()->GetName(targetName);
		//target.GetActor->
		UE_LOG(LogTemp, Log, TEXT("%s"),*targetName);
		if (target.GetActor()->Tags.Contains("Enemy"))
		{
			ALunarticMonster* Monster = Cast<ALunarticMonster>(target.GetActor());
			Monster->OnTakeDamage(Weapon[WeaponType].Damage);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Fail"));
	}
}

void ALunarticPlayerController::Shoot()
{
	notShooting = false;
	
	ACharacter* const MyCharacter = GetCharacter();
	
	MuzzleOffset = MyCharacter->GetActorRotation().Vector() * 30;

	FVector MuzzleLocation = MyCharacter->GetActorLocation() + MuzzleOffset;
	FRotator MuzzleRotation = MyCharacter->GetActorRotation();

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = MyCharacter;
		SpawnParams.Instigator = MyCharacter->GetInstigator();
		AAProjectile* Projectile = World->SpawnActor<AAProjectile>(MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
			Projectile->Damage = Weapon[WeaponType].Damage;
		}
	}
}

void ALunarticPlayerController::ShootExplosive()
{
	notShooting = false;

	ALunarticCharacter* const MyCharacter = Cast<ALunarticCharacter>(GetCharacter());

	MuzzleOffset = MyCharacter->GetActorRotation().Vector() * 30;

	FVector MuzzleLocation = MyCharacter->GetActorLocation() + MuzzleOffset;
	FRotator MuzzleRotation = MyCharacter->GetActorRotation();

	UWorld* World = GetWorld();
	if (World)
	{
		FVector startLoc = MyCharacter->GetActorLocation();      // 발사 지점
		FVector targetLoc = MyCharacter->GetCursorToWorld()->GetComponentLocation();;  // 타겟 지점.
		float arcValue = 0.4f;                       // ArcParam (0.0-1.0)
		FVector outVelocity = FVector::ZeroVector;   // 결과 Velocity
		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = MyCharacter;
			SpawnParams.Instigator = MyCharacter->GetInstigator();
			AExplosive* Projectile = World->SpawnActor<AExplosive>(MuzzleLocation, MuzzleRotation, SpawnParams);

			
			Projectile->Damage = Weapon[WeaponType].Damage;
			Projectile->ProjectileMeshComponent->SetLinearDamping(0);
			Projectile->ProjectileMeshComponent->AddImpulse(outVelocity * 14.7);
		}
	}
}

void ALunarticPlayerController::AttackLimit()
{
	notShooting = true;
}
