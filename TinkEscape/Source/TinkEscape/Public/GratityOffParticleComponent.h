// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "GratityOffParticleComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class TINKESCAPE_API UGratityOffParticleComponent : public UParticleSystemComponent
{
	GENERATED_BODY()

private:

	UGratityOffParticleComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UStaticMeshComponent* CollisionMesh = nullptr;

	
};
