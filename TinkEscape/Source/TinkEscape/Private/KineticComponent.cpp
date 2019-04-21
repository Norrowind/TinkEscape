// Fill out your copyright notice in the Description page of Project Settings.

#include "KineticComponent.h"
#include "Classes/Engine/World.h"
#include "Public/TimerManager.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "GunComponent.h"
#include "Projectile.h"
#include "Tink.h"

// Sets default values for this component's properties
UKineticComponent::UKineticComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UKineticComponent::BeginPlay()
{
	Super::BeginPlay();

	Tink = Cast<ATink>(GetOwner());
	Gun = GetOwner()->FindComponentByClass<UGunComponent>();

	
}

bool UKineticComponent::IsCharging()
{
	return bIsCharging;
}

void UKineticComponent::KineticShotPowerUp()
{
	GetWorld()->GetTimerManager().SetTimer(KineticShotPowerUpTimer, 15.0f, false);
	bIsCharging = true;
}

void UKineticComponent::KineticShot()
{
	if (!ensure(Tink && Gun && KineticShotProjectile)) { return; }

	bIsCharging = false;
	float ShotHoldingTime = GetWorld()->GetTimerManager().GetTimerElapsed(KineticShotPowerUpTimer);
	float RawKineticEnergySpent = ShotHoldingTime * KineticEnergySpentForSecond;
	float KineticEnergySpentForShot = FMath::Clamp(RawKineticEnergySpent, 0.0f, Tink->GetKineticEnergy());
	float ProjectileScaleParametr = FMath::Clamp(ShotHoldingTime, MinKineticShotProjectileSize, MaxKineticShotProjectileSize);

	Tink->SetKinetickEnergyExpend(KineticEnergySpentForShot);
	
	GetWorld()->GetTimerManager().ClearTimer(KineticShotPowerUpTimer);

	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>
		(
			KineticShotProjectile,
			Gun->GetSocketLocation(FName("Projectile")),
			Gun->GetSocketRotation(FName("Projectile"))
			);
	if (SpawnedProjectile)
	{
		SpawnedProjectile->SetActorScale3D(FVector(ProjectileScaleParametr, ProjectileScaleParametr, ProjectileScaleParametr));
		SpawnedProjectile->SetProjectileImpulseStrength(KineticEnergySpentForShot * MinImpulseStrength);
		SpawnedProjectile->LaunchProjectile(KineticShotLaunchSpeed);
	}
}

void UKineticComponent::GravityOffShot()
{
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>
		(
			GravityOffProjectile,
			Gun->GetSocketLocation(FName("Projectile")),
			Gun->GetSocketRotation(FName("Projectile"))
			);
	if (SpawnedProjectile)
	{
		SpawnedProjectile->OnProjectileHitSpecialAction.AddDynamic(this, &UKineticComponent::GravityOffHit);
		SpawnedProjectile->LaunchProjectile(GravityOffShotLaunchSpeed);
	}
}

void UKineticComponent::GravityOffHit(AActor * HittedActor)
{
	UStaticMeshComponent* HittedMesh = HittedActor->FindComponentByClass<UStaticMeshComponent>();
	UE_LOG(LogTemp, Warning, TEXT("StaticMesh name: %s"), *HittedMesh->GetName())
	if (HittedMesh)
		{
			if (HittedMesh->IsSimulatingPhysics())
			{
				
				if (HittedMesh->IsGravityEnabled())
				{
					
					HittedMesh->SetEnableGravity(false);
					HittedMesh->SetLinearDamping(GravityOffLinearDamping);
					HittedMesh->SetAngularDamping(GravityOffAngularDamping);
					Tink->SetKinetickEnergyExpend(KineticEnergyForGravityOff);
				}
				else if(!HittedMesh->IsGravityEnabled())
				{
					HittedMesh->SetEnableGravity(true);
					HittedMesh->SetLinearDamping(GravityOnLinearDamping);
					HittedMesh->SetAngularDamping(GravityOnAngularDamping);
				}
			}
		}
}


