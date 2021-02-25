// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_FlameThrower.h"

AEnemy_FlameThrower::AEnemy_FlameThrower()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(90.0f);
	Capsule->SetCapsuleRadius(60.0f);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BODY(TEXT("StaticMesh'/Game/Model/Flame_thrower/SM_flame_thrower.SM_flame_thrower'"));

	if (BODY.Succeeded())
	{
		Body->SetStaticMesh(BODY.Object);
	}

	RootComponent = Capsule;
	Body->SetupAttachment(Capsule);

	Flame1 = CreateDefaultSubobject<UNiagaraComponent>("Flame1");
	Flame2 = CreateDefaultSubobject<UNiagaraComponent>("Flame2");
	Flame1->SetupAttachment(Body);
	Flame2->SetupAttachment(Body);


	BackFire1 = CreateDefaultSubobject<UNiagaraComponent>("BackFire1");
	BackFire2 = CreateDefaultSubobject<UNiagaraComponent>("BackFire2");
	BackFire1->SetupAttachment(Body);
	BackFire2->SetupAttachment(Body);

	BottomFire = CreateDefaultSubobject<UNiagaraComponent>("BottomFire");
	BottomFire->SetupAttachment(Body);

	AIControllerClass = AEnemy_FlameThrower_Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("511"));

	OnAttack = false;


}

void AEnemy_FlameThrower::BeginPlay()
{
	Super::BeginPlay();

	TargetCharacter = Cast<ALunarticCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Flame1->Deactivate();
	Flame2->Deactivate();
	HP = 50;
}

void AEnemy_FlameThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator tmp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetCharacter->GetActorLocation());
	SetActorRotation(FMath::Lerp(FQuat(GetActorRotation()), FQuat(tmp), 0.05f));

	if (OnAttack && FVector::Dist(GetActorLocation(), TargetCharacter->GetActorLocation()) >= 300)
	{
		OnAttackEnd.Broadcast();
		Flame1->Deactivate();
		Flame2->Deactivate();
		GetWorldTimerManager().ClearTimer(FlameThrowerTimerHandle);
		OnAttack = false;
	}
}

bool AEnemy_FlameThrower::AttackAvailable()
{
	FRotator tmp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetCharacter->GetActorLocation());
	if (GetActorRotation().Equals(tmp, 10))
	{
		return true;
	}

	return false;
}

void AEnemy_FlameThrower::Attack()
{
	if (!OnAttack)
	{
		OnAttack = true;
		Flame1->Activate();
		Flame2->Activate();
		GetWorldTimerManager().SetTimer(FlameThrowerTimerHandle, this, &AEnemy_FlameThrower::FlameDamage, 0.1f, true, 0.1f);
	}
	
}

void AEnemy_FlameThrower::FlameDamage()
{
	FVector Location = Body->GetComponentLocation() + FVector(0, 65, 95);

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ignoreActors;
	ignoreActors.Init(this, 1);
	
	TArray<AActor*> outActors;
	float radius = 300.0f;

	UClass* seekClass = ALunarticCharacter::StaticClass();
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Location, radius, traceObjectTypes, seekClass, ignoreActors, outActors);

	for (AActor* overlappedActor : outActors)
	{
		ALunarticCharacter* Character = Cast<ALunarticCharacter>(overlappedActor);
		
		FRotator Calc = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetCharacter->GetActorLocation());
		if (GetActorRotation().Equals(Calc, 15))
		{
			Character->OnTakeDamage(3);
		}
	}
}