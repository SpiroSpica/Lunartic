// Fill out your copyright notice in the Description page of Project Settings.


#include "LunarticMonster.h"
#include "LunarticMonsterController.h"

// Sets default values
ALunarticMonster::ALunarticMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ACharacter* const MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	
	Capsule->SetCapsuleHalfHeight(96.0f);
	Capsule->SetCapsuleRadius(42.0f);
	RootComponent = Capsule;
	MeshComp->SetupAttachment(Capsule);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH(TEXT("'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (MESH.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MESH.Object);
	}
	MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	if (ANIM.Succeeded())
	{
		MeshComp->SetAnimInstanceClass(ANIM.Class);
	}
	GetCharacterMovement()->bOrientRotationToMovement = true;
	AIControllerClass = ALunarticMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ALunarticMonster::BeginPlay()
{
	Super::BeginPlay();

	
	
	
}

// Called every frame
void ALunarticMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
