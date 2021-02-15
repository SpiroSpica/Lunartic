// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarticCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "LunarticMonsterController.h"
#include "Engine/World.h"

ALunarticCharacter::ALunarticCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Outfit = CreateDefaultSubobject<UStaticMeshComponent>("Appearance");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMesh(TEXT("'/Game/Model/Player/SM_player.SM_player'"));
	if (StaticMesh.Succeeded())
	{
		Outfit->SetStaticMesh(StaticMesh.Object);
	}

	Outfit->SetupAttachment(RootComponent);
	HoverFL = CreateDefaultSubobject<UNiagaraComponent>("Hover1");
	HoverFL->SetupAttachment(Outfit);

	HoverFR = CreateDefaultSubobject<UNiagaraComponent>("Hover2");
	HoverFR->SetupAttachment(Outfit);

	HoverBL = CreateDefaultSubobject<UNiagaraComponent>("Hover3");
	HoverBL->SetupAttachment(Outfit);

	HoverBR = CreateDefaultSubobject<UNiagaraComponent>("Hover4");
	HoverBR->SetupAttachment(Outfit);

	Shoot = CreateDefaultSubobject<UNiagaraComponent>("ShootFire");
	Shoot->SetupAttachment(Outfit);

	HoverSmoke = CreateDefaultSubobject<UNiagaraComponent>("HoverSmoke");
	HoverSmoke->SetupAttachment(Outfit);
	

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	EnemyCount = 0;
	RequiredKill = 30;
	HP = 200;

	PastRotationYaw = 0;
}

void ALunarticCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	GetCharacterMovement()->bOrientRotationToMovement = false;
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
			
			FVector direction = TraceHitResult.Location - GetActorLocation();
			FRotator Rot = FRotator(0,FRotationMatrix::MakeFromX(direction).Rotator().Yaw,0);
			
			SetActorRotation(Rot);
		}
	}

	float CurrentYaw = GetActorRotation().Yaw;

	if (PastRotationYaw < CurrentYaw) 
	{
		HoverFL->Deactivate();
		HoverFR->Activate();
		HoverBL->Activate();
		HoverBR->Deactivate();
	}
	else if (PastRotationYaw > CurrentYaw)
	{
		HoverFL->Activate();
		HoverFR->Deactivate();
		HoverBL->Deactivate();
		HoverBR->Activate();
	}
	else
	{
		HoverFL->Deactivate();
		HoverFR->Deactivate();
		HoverBL->Deactivate();
		HoverBR->Deactivate();
	}
	PastRotationYaw = CurrentYaw;
}

void ALunarticCharacter::BeginPlay()
{
	Super::BeginPlay();
	Shoot->Deactivate();
	HoverFL->Deactivate();
	HoverFR->Deactivate();
	HoverBL->Deactivate();
	HoverBR->Deactivate();

}

void ALunarticCharacter::OnEnemyKill()
{
	EnemyCount++;
}

void ALunarticCharacter::OnTakeDamage(int Damage)
{
	HP -= Damage;

	if (HP <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("GameOver"));
	}
}

void ALunarticCharacter::FireEffect(bool firing)
{
	if (firing)
	{
		Shoot->Activate();
	}
	else
	{
		Shoot->Deactivate();
	}
}

int ALunarticCharacter::GetHP()
{
	return HP;
}

int ALunarticCharacter::GetKillCount()
{
	return EnemyCount;
}