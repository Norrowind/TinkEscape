// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "Classes/Engine/World.h"
#include "Engine/Public/TimerManager.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->SetupAttachment(RootComponent);

	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Particle"));
	LaunchParticle->SetupAttachment(RootComponent);

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion Particle"));
	ExplosionParticle->SetupAttachment(RootComponent);
	ExplosionParticle->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(CollisionMesh)) { return; }
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	if (!ensure(ProjectileMovement)) { return; }
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovement->Activate();
}

void AProjectile::SetProjectileImpulseStrength(float ImpulseStrength)
{
	if (!ensure(ExplosionForce)) { return; }
	ExplosionForce->ImpulseStrength = ImpulseStrength;
}

//Called when Projectile hit something
void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{	
	if (!ensure(LaunchParticle && ExplosionParticle && ExplosionForce)) {return;}
	OnProjectileHitSpecialAction.Broadcast(OtherActor);
	LaunchParticle->Deactivate();
	ExplosionParticle->Activate();
	ExplosionForce->FireImpulse();

	FTimerHandle DestroyTimer;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AProjectile::OnTimeToDestroy, DestroyDelay);
	CollisionMesh->SetNotifyRigidBodyCollision(false);
}

void AProjectile::OnTimeToDestroy()
{
	OnProjectileHitSpecialAction.RemoveAll(this);
	Destroy();
}

