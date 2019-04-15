// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingComponent.h"
#include "Classes/Engine/World.h"
#include "TinkController.h"
#include "Tink.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "GunComponent.h"

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
	SpawnedGhostPlatform->FindComponentByClass<UStaticMeshComponent>()->OnComponentHit.AddDynamic(this, &UBuildingComponent::OnGhostPlatformHit);
	bIsBuilding = true;
}

void UBuildingComponent::MoveGhostPlatform()
{
	SpawnedGhostPlatform->TeleportTo(TinkController->GetSightRayHitResult().TraceEnd, FRotator::ZeroRotator);
}

void UBuildingComponent::PlaceReadyPlatform()
{	
	bIsBuilding = false;
	if (!ensure(Gun)) { return; }
	if (Tink->GetBuildingEnergy() >= BuildingEnergyCost)
	{
		Gun->Fire(BuildingProjectile);
	}
	else
	{
		SpawnedGhostPlatform->Destroy();
	}

}

void UBuildingComponent::OnGhostPlatformHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (!ensure(Tink)) { return; }
	if (!ensure(SpawnedGhostPlatform)) { return; }
	FVector ReadyPlatformSpawnLocation = SpawnedGhostPlatform->GetActorLocation();
	SpawnedReadyPlatform = GetWorld()->SpawnActor<AActor>
		(
			ReadyPlatform,
			ReadyPlatformSpawnLocation,
			FRotator::ZeroRotator
			);
	SpawnedReadyPlatform->FindComponentByClass<UStaticMeshComponent>()->OnComponentHit.AddDynamic(this, &UBuildingComponent::OnReadyPlatformHit);
	Tink->SetBuildingEnergyExpend(BuildingEnergyCost);
	SpawnedGhostPlatform->Destroy();
}

void UBuildingComponent::OnReadyPlatformHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{

}


void UBuildingComponent::ComsumeBuildingEnergy()
{
	if (TinkController->GetSightRayHitResult().GetActor())
	{
		auto Target = TinkController->GetSightRayHitResult().GetActor();
		auto TargetName = Target->FindComponentByClass<UStaticMeshComponent>()->GetName();
		if (TargetName == TEXT("ReadyPlatform"))
		{
			Target->Destroy();
			Tink->SetBuildingEnergyExpend(BuildingEnergyForPlatform);
		}
	}
}

