// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidMovementComponent.h"
#include "Classes/Engine/World.h"
#include "Public/TimerManager.h"
#include "DroidBody.h"
#include "Tink.h"
#include "Classes/Particles/ParticleSystemComponent.h"

void UDroidMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	DroidBody = GetOwner()->FindComponentByClass<UDroidBody>();
	Tink = Cast<ATink>(GetOwner());
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

void UDroidMovementComponent::PowerUpJump()
{
	GetWorld()->GetTimerManager().SetTimer(JumpPowerTimer, 15.0f, false);

}

void UDroidMovementComponent::StartJump()
{	
	if (!ensure(Tink && DroidBody)) { return; }
	float RawKineticEnergySpentForJump = GetWorld()->GetTimerManager().GetTimerElapsed(JumpPowerTimer) * KineticEnergyJumpCostForSecond;
	KineticEnergySpentForJump = FMath::Clamp(RawKineticEnergySpentForJump, 0.0f, Tink->GetKineticEnergy());
	Tink->SetKinetickEnergyExpend(KineticEnergySpentForJump);

	GetWorld()->GetTimerManager().ClearTimer(JumpPowerTimer);

	DroidBody->SetLinearDamping(0.3f);
	DroidBody->SetAngularDamping(0.6f);
	FVector ForceForJump = DroidBody->GetUpVector() * MinForceToApplyForJump * KineticEnergySpentForJump;
	DroidBody->AddForce(ForceForJump);

}

