// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidMovementComponent.h"
#include "DroidBody.h"

void UDroidMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	DroidBody = GetOwner()->FindComponentByClass<UDroidBody>();
}

void UDroidMovementComponent::IntendMoveForward(float AxisValue)
{
	if (!ensure(DroidBody)) { return; }
	DroidBody->SetDirectInputMovement(AxisValue);
}

void UDroidMovementComponent::IntendMoveRight(float AxisValue)
{
	if (!ensure(DroidBody)) { return; }
	DroidBody->SetSideInputMovement(AxisValue);
}
