// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KineticComponent.generated.h"

//Forward declaration
class ATink;
class AProjectile;
class UGunComponent;
class UBuildingComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINKESCAPE_API UKineticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKineticComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void KineticShotPowerUp();

	void KineticShot();

	void GravityOffShot();

	UFUNCTION(BlueprintCallable, Category = "BuildingGun")
	void GravityOffHit(AActor * HittedActor);

	bool IsCharging();

private:

	ATink* Tink = nullptr;

	UGunComponent* Gun = nullptr;

	FTimerHandle KineticShotPowerUpTimer;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile>KineticShotProjectile;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile>GravityOffProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinImpulseStrength = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float KineticEnergySpentForSecond = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float KineticEnergyForGravityOff = -25.0f; //Should be negative

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float KineticShotLaunchSpeed = 7000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GravityOffShotLaunchSpeed = 7000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinKineticShotProjectileSize = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxKineticShotProjectileSize = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GravityOffLinearDamping = 4.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GravityOffAngularDamping = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GravityOnLinearDamping = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GravityOnAngularDamping = 0.3f;

	bool bIsCharging = false;


		
};
