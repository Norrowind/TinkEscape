// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ATinkController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINKESCAPE_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlaceGhostPlatform();

	void PlaceReadyPlatform();

private:

	void MoveGhostPlatform();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor>GhostPlatform;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor>ReadyPlatform;
	
	ATinkController* TinkController = nullptr;

	AActor* SpawnedGhostPlatform = nullptr;

	bool bIsBuilding = false;
};
