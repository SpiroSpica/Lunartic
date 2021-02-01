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

	static ConstructorHelpers::FObjectFinder<UBlueprint> Unit(TEXT("'/Game/Enemy/Enemy_Cannon.Enemy_Cannon'"));
	if (Unit.Object != nullptr)
	{
		UnitToSpawn = (UClass*)Unit.Object->GeneratedClass;
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
	ALunarticMonster* tmp = Cast<ALunarticMonster>(GetWorld()->SpawnActor(UnitToSpawn, &SpawnLocation));
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
		StageClear();
	}

}

void AMonsterSpawner::StageClear()
{
	for (int i = 0; i < UnitSave.Num(); i++)
	{
		if (UnitSave[i] != nullptr)
		{
			UnitSave[i]->Destroy();
		}
	}
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

}

