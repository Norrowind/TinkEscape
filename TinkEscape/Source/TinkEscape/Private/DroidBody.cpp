// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidBody.h"
#include "HoverComponent.h"

// Sets default values
UDroidBody::UDroidBody()
{
	// Set this component to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}

//Move when hover is working
void UDroidBody::OnHover()
{
	MoveForward();
	MoveRight();
	InputMovement.X = 0.0f;
	InputMovement.Y = 0.0f;
}

void UDroidBody::BeginPlay()
{
	Super::BeginPlay();	
	HoverComponent = GetOwner()->FindComponentByClass<UHoverComponent>();
	HoverComponent->OnHover.AddDynamic(this, &UDroidBody::OnHover);
}

void UDroidBody::SetDirectInputMovement(float Throw)
{

	InputMovement.X = FMath::Clamp(Throw, -1.0f, 1.0f);
}

void UDroidBody::SetSideInputMovement(float Throw)
{

	InputMovement.Y = FMath::Clamp(Throw, -1.0f, 1.0f);
}

//Handle movement by adding force forward and backward
void UDroidBody::MoveForward()
{
	auto ForceApplied = GetForwardVector() * InputMovement.X * DrivingForce;
	AddForce(ForceApplied);
}

//Handle movement by adding force right and left
void UDroidBody::MoveRight()
{
	auto ForceApplied = GetRightVector() * InputMovement.Y * DrivingForce;
	AddForce(ForceApplied);
}


