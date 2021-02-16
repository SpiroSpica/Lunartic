// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Cannon.h"

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
	Flash = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Flash"));

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


	Legs->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("'/Game/Model/Heavy_cannon/Cannon_AnimBP.Cannon_AnimBP_C'"));
	if (ANIM.Succeeded())
	{
		Legs->SetAnimInstanceClass(ANIM.Class);
	}
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	AIControllerClass = AEnemy_Cannon_Controller::StaticClass();
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
	UNiagaraFunctionLibrary::SpawnSystemAttached(Flash, Cannon, FName("root"), FVector(0, 0, 270), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, true);
	UE_LOG(LogTemp, Warning, TEXT("Attacked2"));

	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	
	FVector ExplosionLocation = FirePlace;

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
	UClass* seekClass = ALunarticCharacter::StaticClass(); // NULL;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), ExplosionLocation, radius, traceObjectTypes, seekClass, ignoreActors, outActors);

	UE_LOG(LogTemp, Warning, TEXT("Number found: %d"), outActors.Num());

	for (AActor* overlappedActor : outActors)
	{
		ALunarticCharacter* Player = Cast<ALunarticCharacter>(overlappedActor);
		Player->GetCharacterMovement()->AddRadialImpulse(ExplosionLocation, radius, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
		Player->OnTakeDamage(100);
	}



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