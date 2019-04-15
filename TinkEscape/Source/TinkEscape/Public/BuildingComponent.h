// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ATinkController;
class ATink;
class AProjectile;
class UGunComponent;

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

	void ComsumeBuildingEnergy();

private:

	void MoveGhostPlatform();

	UFUNCTION()
	void OnGhostPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnReadyPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor>GhostPlatform;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor>ReadyPlatform;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile>BuildingProjectile;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile>ConsumeProjectile;

	ATink* Tink = nullptr;
	
	ATinkController* TinkController = nullptr;

	UGunComponent* Gun = nullptr;

	AActor* SpawnedReadyPlatform = nullptr;

	AActor* SpawnedGhostPlatform = nullptr;

	bool bIsBuilding = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BuildingEnergyCost = 25;

	int32 BuildingEnergyForPlatform = -15;
};
