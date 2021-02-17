// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	SpawnPoint = CreateDefaultSubobject<UParticleSystemComponent>("SpawnPoint");

	SpawnInterval = 1;
	isGameRunning = true;

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		BuildingMesh->SetStaticMesh(MeshAsset.Object);
		//BuildingMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}

	auto ParticleSystem = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem.TutorialParticleSystem'"));
	if (ParticleSystem.Object != nullptr)
	{
		SpawnPoint->SetTemplate(ParticleSystem.Object);
	}

	SpawnPoint->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	static ConstructorHelpers::FObjectFinder<UBlueprint> UnitF(TEXT("Blueprint'/Game/Enemy/FlameThrower/Enemy_FlameThrower_BP.Enemy_FlameThrower_BP'"));
	if (UnitF.Object != nullptr)
	{
		UnitFlame = (UClass*)UnitF.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> UnitC(TEXT("Blueprint'/Game/Enemy/Cannon/Enemy_Cannon_BP.Enemy_Cannon_BP'"));
	if (UnitC.Object != nullptr)
	{
		UnitCannon = (UClass*)UnitC.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	RootComponent = BuildingMesh;
	SpawnPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnPoint->SetRelativeLocation(FVector(150, 0, 0));

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMonsterSpawner::SpawnUnit, SpawnInterval, true);
}

void AMonsterSpawner::SpawnUnit()
{
	FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	ALunarticMonster* tmp = Cast<ALunarticMonster>(GetWorld()->SpawnActor(UnitFlame, &SpawnLocation));
	UnitSave.Emplace(tmp);
}


void AMonsterSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isGameRunning && GetWorld()->GetAuthGameMode<ALunarticGameMode>()->isStageCleared())
	{

		isGameRunning = false;
		StageClear(GetWorld()->GetAuthGameMode<ALunarticGameMode>()->isSucceeded());
	}
}

void AMonsterSpawner::StageClear(bool Succeeded)
{
	if (Succeeded)
	{
		for (int i = 0; i < UnitSave.Num(); i++)
		{
			if (UnitSave[i] != nullptr)
			{
				UnitSave[i]->Destroy();
			}
		}
	}
	
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}

