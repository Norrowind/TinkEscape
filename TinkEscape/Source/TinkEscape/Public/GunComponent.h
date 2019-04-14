// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GunComponent.generated.h"

/**
 * Method which realized gun aiming
 */

//Forward declaration
class ATinkController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TINKESCAPE_API UGunComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UGunComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimingAtLocation(FVector AimLocation);

	void MoveGun(FVector AimDirection);

	ATinkController* TinkController = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LaunchSpeed = 16000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 70.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinDegreesElevation = - 15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesElevation = 85.0f;
	
};
