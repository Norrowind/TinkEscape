// Fill out your copyright notice in the Description page of Project Settings.

#include "GunComponent.h"
#include "TinkController.h"
#include "Classes/Engine/World.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"




// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGunComponent::BeginPlay()
{
	Super::BeginPlay();
	TinkController = Cast<ATinkController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void UGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ensure(TinkController))
	{
		AimingAtLocation(TinkController->GetSightRayHitResult().TraceEnd);
	}

}

//Get tracing end point and elevate guns to aim on it
void UGunComponent::AimingAtLocation(FVector AimLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = GetSocketLocation(FName("Projectile"));
	UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false

	);

	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveGun(AimDirection);
}

//Move gun based on delta rotator between current gun position and aiming position
void UGunComponent::MoveGun(FVector AimDirection)
{
	FRotator GunRotator = GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - GunRotator;
	float DeltaRotatorFixedPitch = FMath::Clamp<float>(DeltaRotator.Pitch, -1.0f, 1.0f);
	float RawRotationChange = DeltaRotatorFixedPitch * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RotationChange = FMath::Clamp<float>(RawRotationChange, MinDegreesElevation, MaxDegreesElevation);
	AddRelativeRotation(FRotator(RotationChange, 0.0f, 0.0f));

}
