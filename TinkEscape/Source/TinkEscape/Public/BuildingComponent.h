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

	void PlatformBuildShot();

	void ComsumePlatformShot();

	UFUNCTION(BlueprintCallable, Category = "BuildingGun")
	void OnBuildingHit(AActor * OtherActor);

	UFUNCTION(BlueprintCallable, Category = "BuildingGun")
	void OnConsumeHit(AActor * OtherActor);

private:

	void MoveGhostPlatform();

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

	AActor* SpawnedGhostPlatform = nullptr;

	FString GhostPlatformName;
	FString ReadyPlatformName;

	bool bIsBuilding = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BuildingEnergyCost = 25;

	//Should be negative
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BuildingEnergyForPlatformConsume = -15;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float BuildShotLaunchSpeed = 7000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ConsumeShotLaunchSpeed = 7000.0f;

};
