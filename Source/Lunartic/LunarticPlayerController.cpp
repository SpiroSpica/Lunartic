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
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALunarticPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (isFire && notShooting)
	{
		//Shoot();
		HitScan();
	}
}

void ALunarticPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this,  &ALunarticPlayerController::AttackLimit, 0.1f, true, 0.1f);
}

void ALunarticPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALunarticPlayerController::StartShoot);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ALunarticPlayerController::EndShoot);

	InputComponent->BindAxis(TEXT("MoveForWard"), this, &ALunarticPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ALunarticPlayerController::LeftRight);
	
}

void ALunarticPlayerController::StartShoot()
{
	isFire = true;
}

void ALunarticPlayerController::EndShoot()
{
	isFire = false;
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
		}
	}
}

void ALunarticPlayerController::AttackLimit()
{
	notShooting = true;
}
