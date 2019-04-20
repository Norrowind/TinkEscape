// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingComponent.h"
#include "Classes/Engine/World.h"
#include "Public/TimerManager.h"
#include "TinkController.h"
#include "Tink.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "GunComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TinkController = Cast<ATinkController>(GetWorld()->GetFirstPlayerController());
	Tink = Cast<ATink>(GetOwner());
	Gun = GetOwner()->FindComponentByClass<UGunComponent>();

}


// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsBuilding)
	{
		MoveGhostPlatform();
	}
}

bool UBuildingComponent::IsBuilding() const
{
	return bIsBuilding;
}

void UBuildingComponent::PlaceGhostPlatform()
{
	if (!ensure(TinkController)) { return; }
	if (!ensure(GhostPlatform)) { return; }
	SpawnedGhostPlatform = GetWorld()->SpawnActor<AActor>
	(
		GhostPlatform,
		TinkController->GetSightRayHitResult().TraceEnd,
		FRotator::ZeroRotator
	);
	GhostPlatformName = SpawnedGhostPlatform->FindComponentByClass<UStaticMeshComponent>()->GetName();
	bIsBuilding = true;
}

void UBuildingComponent::MoveGhostPlatform()
{
	SpawnedGhostPlatform->TeleportTo(TinkController->GetSightRayHitResult().TraceEnd, FRotator::ZeroRotator);
}

//Shot building projectile and bind platform build logic
void UBuildingComponent::PlatformBuildShot()
{	
	bIsBuilding = false;
	if (!ensure(Gun)) { return; }
	if (!ensure(Tink)) { return; }

	if (Tink->GetBuildingEnergy() >= BuildingEnergyCost)
	{
		if (!ensure(BuildingProjectile)) { return; }

		//Spawn projectile on the socket location of gun
		AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>
			(
				BuildingProjectile,
				Gun->GetSocketLocation(FName("Projectile")),
				Gun->GetSocketRotation(FName("Projectile"))
			);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->OnProjectileHitSpecialAction.AddDynamic(this, &UBuildingComponent::OnBuildingHit);
			SpawnedProjectile->LaunchProjectile(BuildShotLaunchSpeed);
		}
	}
	else
	{
		SpawnedGhostPlatform->Destroy();
	}

}

//Spawning Ready Platform when projectile hit Ghost Platform
void UBuildingComponent::OnBuildingHit(AActor * HittedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBuildingHit called"))

	if (!ensure(Tink)) { return; }
	if (!ensure(SpawnedGhostPlatform)) { return; }

	//Compare ghost platform static mesh name with mesh component name of hitted actor 
	FString OtherActorName = HittedActor->FindComponentByClass<UStaticMeshComponent>()->GetName();
	if (OtherActorName == GhostPlatformName)
	{
		FVector ReadyPlatformSpawnLocation = SpawnedGhostPlatform->GetActorLocation();
		AActor* SpawnedReadyPlatform = GetWorld()->SpawnActor<AActor>
			(
				ReadyPlatform,
				ReadyPlatformSpawnLocation,
				FRotator::ZeroRotator
			);
		ReadyPlatformName = SpawnedReadyPlatform->FindComponentByClass<UStaticMeshComponent>()->GetName();
		Tink->SetBuildingEnergyExpend(BuildingEnergyCost);
		SpawnedGhostPlatform->Destroy();
	}
	else
	{
		SpawnedGhostPlatform->Destroy();
	}
}

//Shot consume projectile and bind paltform consume logic
void UBuildingComponent::ComsumePlatformShot()
{
	UE_LOG(LogTemp, Warning, TEXT("OnConsumegHit called"))

	if (!ensure(Gun)) { return; }
	if (!ensure(ConsumeProjectile)) { return; }

	//Spawn projectile on the socket location of gun
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>
		(
			ConsumeProjectile,
			Gun->GetSocketLocation(FName("Projectile")),
			Gun->GetSocketRotation(FName("Projectile"))
			);
	if (SpawnedProjectile)
	{
		SpawnedProjectile->OnProjectileHitSpecialAction.AddDynamic(this, &UBuildingComponent::OnConsumeHit);
		SpawnedProjectile->LaunchProjectile(ConsumeShotLaunchSpeed);
	}


}

//Destroy paltform and add building energy
void UBuildingComponent::OnConsumeHit(AActor * HittedActor)
{
	if (!ensure(Tink)) { return; }

	//Compare ready platform static mesh name with mesh component name of hitted actor 
	FString OtherActorName = HittedActor->FindComponentByClass<UStaticMeshComponent>()->GetName();
	if (OtherActorName == ReadyPlatformName)
	{
		HittedActor->Destroy();
		Tink->SetBuildingEnergyExpend(BuildingEnergyForPlatformConsume);
	}

}


