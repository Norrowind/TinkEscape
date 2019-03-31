// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "DroidMovementComponent.generated.h"

/**
 * Component which handle inputs of the droids
 */

//Forward declaration
class UDroidBody;
class ATink;
class UHoverComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class TINKESCAPE_API UDroidMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void IntendMoveForward(float AxisValue);

	void IntendMoveRight(float AxisValue);

	void PowerUpJump();

	void StartJump();

private:
	UDroidBody* DroidBody = nullptr;

	ATink* Tink = nullptr;

	UHoverComponent* HoverComponent = nullptr;

	//Timer which handle power of jump based on, how long jump button pressed
	FTimerHandle JumpPowerTimer;
	
	float KineticEnergySpentForJump;

	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float KineticEnergyJumpCostForSecond = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float MinForceToApplyForJump = 2000000.0f;


};
