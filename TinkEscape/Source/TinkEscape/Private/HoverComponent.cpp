// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverComponent.h"
#include "DroidBody.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Engine/World.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	DroidBody = GetOwner()->FindComponentByClass<UDroidBody>();
	DroidBody->SetSimulatePhysics(true);
	HoveringParticle = GetOwner()->FindComponentByClass<UParticleSystemComponent>();
	HoveringParticle->bAutoActivate = false;
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Hover();
}

void UHoverComponent::Hover()
{
	FHitResult OutHitResult;
	if (IsBelowToTheGroundEnoughToHover(OutHitResult))
	{
		ActivateHover(OutHitResult);
	}
	else
	{	
		HoveringParticle->Deactivate();
		DroidBody->SetLinearDamping(NormalLinearDamping);
		DroidBody->SetAngularDamping(NormalAngularDamping);
		OnAir.Broadcast();
	}
}

void UHoverComponent::ActivateHover(const FHitResult HitResult )
{
	ForceToApply = ForceToHover;
	ApplyForceToHover(HitResult);
	DroidBody->SetLinearDamping(LinearHoverDamping);
	DroidBody->SetAngularDamping(AngularHoverDamping);
	HoveringParticle->Activate();
	OnHover.Broadcast();
}

//Tracing a ray to the ground
bool UHoverComponent::IsBelowToTheGroundEnoughToHover(FHitResult & OutHitResult)
{
	if (ensure(DroidBody))
	{
		return GetWorld()->LineTraceSingleByChannel
		(
			OutHitResult,
			DroidBody->GetComponentLocation(),
			DroidBody->GetComponentLocation() - FVector(0.0f, 0.0f, TraceLength),
			ECollisionChannel::ECC_Visibility,
			FCollisionQueryParams::DefaultQueryParam.bTraceComplex = true,
			FCollisionResponseParams::DefaultResponseParam
		);
	}
	else
	{
		return false;
	}
}

void UHoverComponent::ApplyForceToHover(const FHitResult HitResult)
{
	float DistanceFromGround = (HitResult.Location - DroidBody->GetComponentLocation()).Size(); //get the length of vector
	float InterpolationResult = FMath::Lerp(ForceToApply, 0.0f, DistanceFromGround / TraceLength);
	FVector VectorHoveringForce = HitResult.ImpactNormal * InterpolationResult;
	if (!ensure(DroidBody)) { return; }
	DroidBody->AddForce(VectorHoveringForce);
}

void UHoverComponent::DeactivateHover()
{
	if (!ensure(DroidBody)) { return; }
	ForceToApply = 0.0f;
	DroidBody->SetLinearDamping(NormalLinearDamping);
	DroidBody->SetAngularDamping(NormalAngularDamping);
	HoveringParticle->Deactivate();
}