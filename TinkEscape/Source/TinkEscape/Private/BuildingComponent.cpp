// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingComponent.h"
#include "Classes/Engine/World.h"
#include "TinkController.h"
#include "Tink.h"
#include "Classes/Components/StaticMeshComponent.h"

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
	bIsBuilding = true;
}

void UBuildingComponent::MoveGhostPlatform()
{
	SpawnedGhostPlatform->TeleportTo(TinkController->GetSightRayHitResult().TraceEnd, FRotator::ZeroRotator);
}

void UBuildingComponent::PlaceReadyPlatform()
{	
	if (!ensure(Tink)) { return; }
	if (!ensure(SpawnedGhostPlatform)) { return; }
	FVector ReadyPlatformSpawnLocation = SpawnedGhostPlatform->GetActorLocation();
	SpawnedGhostPlatform->Destroy();
	if (Tink->GetBuildingEnergy() >= BuildingEnergyCost)
	{
		GetWorld()->SpawnActor<AActor>
			(
				ReadyPlatform,
				ReadyPlatformSpawnLocation,
				FRotator::ZeroRotator
				);
		bIsBuilding = false;
		Tink->SetBuildingEnergyExpend(BuildingEnergyCost);
	}
	
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

