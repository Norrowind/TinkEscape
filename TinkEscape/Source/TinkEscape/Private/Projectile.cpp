// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"

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

	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Particle"));
	AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion Particle"));
	AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
}

