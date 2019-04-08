// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingComponent.h"
#include "Classes/Engine/World.h"
#include "TinkController.h"

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
	FVector ReadyPlatformSpawnLocation = SpawnedGhostPlatform->GetActorLocation();
	SpawnedGhostPlatform->Destroy();
	GetWorld()->SpawnActor<AActor>
		(
			ReadyPlatform,
			ReadyPlatformSpawnLocation,
			FRotator::ZeroRotator
		);
	bIsBuilding = false;
}

