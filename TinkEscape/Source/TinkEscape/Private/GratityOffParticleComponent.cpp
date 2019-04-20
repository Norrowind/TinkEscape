// Fill out your copyright notice in the Description page of Project Settings.

#include "GratityOffParticleComponent.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UGratityOffParticleComponent::UGratityOffParticleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGratityOffParticleComponent::BeginPlay()
{
	CollisionMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	bIsActive = false;
}

void UGratityOffParticleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (CollisionMesh->IsGravityEnabled())
	{
		Deactivate();
	}
	else
	{
		Activate();
	}
}
