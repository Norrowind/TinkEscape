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

UCLASS(meta = (BlueprintSpawnableComponent))
class TINKESCAPE_API UDroidMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void IntendMoveForward(float AxisValue);

	void IntendMoveRight(float AxisValue);

private:
	UDroidBody* DroidBody = nullptr;


};
