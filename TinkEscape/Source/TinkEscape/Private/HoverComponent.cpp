// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverComponent.h"
#include "DroidBody.h"
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
	//Tracing a ray to the ground
	bool bIsBlockingHitFound = GetWorld()->LineTraceSingleByChannel
	(
		OutHitResult,
		DroidBody->GetComponentLocation(),
		DroidBody->GetComponentLocation() - FVector(0.0f, 0.0f, TraceLength),
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams::DefaultQueryParam.bTraceComplex = true,
		FCollisionResponseParams::DefaultResponseParam
	);

	float DistanceFromGround = (OutHitResult.Location - DroidBody->GetComponentLocation()).Size(); //get the length of vector
	float InterpolationResult = FMath::Lerp(ForceToHover, 0.0f, DistanceFromGround / TraceLength);
	FVector ForceToApply = OutHitResult.ImpactNormal * InterpolationResult;

	if (bIsBlockingHitFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("BlockingHitFound"))
			OnHover.Broadcast();
		if (!ensure(DroidBody)) { return; }
		DroidBody->AddForce(ForceToApply);
		DroidBody->SetLinearDamping(LinearHoverDamping);
		DroidBody->SetAngularDamping(AngularHoverDamping);
	}
	else
	{
		DroidBody->SetLinearDamping(NormalLinearDamping);
		DroidBody->SetAngularDamping(NormalAngularDamping);
	}
}
