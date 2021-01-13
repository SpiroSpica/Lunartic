// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "LunarticCharacter.h"
#include "Engine/World.h"

ALunarticPlayerController::ALunarticPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALunarticPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ALunarticPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALunarticPlayerController::Shoot);

	InputComponent->BindAxis(TEXT("MoveForWard"), this, &ALunarticPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ALunarticPlayerController::LeftRight);
	
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

void ALunarticPlayerController::Shoot()
{
	UE_LOG(LogTemp, Log, TEXT("Shoot"));
	
	
		UE_LOG(LogTemp, Log, TEXT("Shoot2"));
		ACharacter* const MyCharacter = GetCharacter();

		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

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