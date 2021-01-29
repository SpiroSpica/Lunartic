// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Cannon.h"
#include "LunarticMonsterController.h"

// Sets default values
AEnemy_Cannon::AEnemy_Cannon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetCharacter = Cast<ALunarticCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(150.0f);
	Capsule->SetCapsuleRadius(100.0f);

	Legs = GetMesh();
	Base = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base"));
	Cannon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cannon"));
	Explosion = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Boom"));

	RootComponent = Capsule;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LEG(TEXT("'/Game/Model/Heavy_cannon/SM_heavy_cannon_legs.SM_heavy_cannon_legs'"));
	if (LEG.Succeeded())
	{
		Legs->SetSkeletalMesh(LEG.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BASE(TEXT("'/Game/Model/Heavy_cannon/SM_heavy_cannon_base.SM_heavy_cannon_base'"));
	if (LEG.Succeeded())
	{
		Base->SetSkeletalMesh(BASE.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CANNON(TEXT("'/Game/Model/Heavy_cannon/SM_heavy_cannon_cannon.SM_heavy_cannon_cannon'"));
	if (CANNON.Succeeded())
	{
		Cannon->SetSkeletalMesh(CANNON.Object);
	}

	FName ParentSocket = TEXT("root");
	Legs->SetupAttachment(Capsule);
	Base->AttachToComponent(Legs, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), ParentSocket);
	Cannon->AttachToComponent(Base, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), ParentSocket);

	/*
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BOOM(TEXT("NiagaraSystem'/Game/VFX/FX/Cannon/NS_cannon_flash.NS_cannon_flash'"));
	if (BOOM.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Niagara Found"));
		Explosion = BOOM.Object;
	}
	*/
	Legs->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("'/Game/Model/Heavy_cannon/Cannon_AnimBP.Cannon_AnimBP_C'"));
	if (ANIM.Succeeded())
	{
		Legs->SetAnimInstanceClass(ANIM.Class);
	}
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	AIControllerClass = ALunarticMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HP = 200;
	OnAttack = false;

	
}

// Called when the game starts or when spawned
void AEnemy_Cannon::BeginPlay()
{
	Super::BeginPlay();
	//Tags.Add("Enemy");
}

// Called every frame
void AEnemy_Cannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!OnAttack)
	{
		FRotator tmp = UKismetMathLibrary::FindLookAtRotation(Cannon->GetComponentLocation(), TargetCharacter->GetActorLocation());
		Base->SetWorldRotation(FMath::Lerp(FQuat(Base->GetComponentRotation()),FQuat(tmp), 0.05f));
	}
}

void AEnemy_Cannon::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attacking"));

	FirePlace = TargetCharacter->GetActorLocation();
	OnAttack = true;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemy_Cannon::Fire, 2.0f, false);

	
}

void AEnemy_Cannon::Fire()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Explosion, FirePlace, FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("Attacked"));
	OnAttackEnd.Broadcast();
	OnAttack = false;
}

bool AEnemy_Cannon::AttackAvailable()
{
	FRotator tmp = UKismetMathLibrary::FindLookAtRotation(Cannon->GetComponentLocation(), TargetCharacter->GetActorLocation());
	if (Base->GetComponentRotation().Equals(tmp, 10))
	{
		return true;
	}
	
	return false;
}