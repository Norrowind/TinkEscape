// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidBody.h"

// Sets default values
UDroidBody::UDroidBody()
{
	// Set this component to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}


void UDroidBody::OnHit(UPrimitiveComponent * HitComponent, AActor * OthetActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	MoveForward();
	MoveRight();
}

void UDroidBody::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UDroidBody::OnHit);
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
	this->AddForce(ForceApplied);
}

//Handle movement by adding force right and left
void UDroidBody::MoveRight()
{
	auto ForceApplied = GetRightVector() * InputMovement.Y * DrivingForce;
	this->AddForce(ForceApplied);
}


