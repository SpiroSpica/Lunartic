// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"

// Sets default values
AAProjectile::AAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PorjectileSceneComponent"));
	}
	/* Add collision sphere and attach to root */
	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->SetCollisionProfileName(TEXT("Bullet"));
		RootComponent = CollisionComponent;
	}

	/* Basic setups for overall projectile movement component setting*/
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1500.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f; 
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	/* add mesh to projectile*/
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		ProjectileMeshComponent->SetCollisionProfileName(TEXT("Bullet"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Resources/Sphere.Sphere'"));

		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Resources/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}

	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAProjectile::OnHit);
}

// Called when the game starts or when spawned
void AAProjectile::BeginPlay()
{
	Super::BeginPlay();

	/* projectile disappears in 5 seconds after it is spawned if not trigger hit event*/
	SetLifeSpan(5);
}

/* Set direction of projectile */
void AAProjectile::FireInDirection(const FVector& ShootDirection) 
{
	AAProjectile::ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

/* Set event when projectile collide with other thing*/
void AAProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.GetActor()->Tags.Contains("Enemy"))
	{
		ALunarticMonster* Target = Cast<ALunarticMonster>(Hit.GetActor());
		Target->OnTakeDamage(Damage);
	}
	Destroy();	
}

/* Set Damage that projectile can give */
void AAProjectile::SetDamage(int Dmg)
{
	Damage = Dmg;
}

