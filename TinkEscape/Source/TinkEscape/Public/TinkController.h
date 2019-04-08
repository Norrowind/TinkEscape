// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TinkController.generated.h"

/**
 * 
 */
UCLASS()
class TINKESCAPE_API ATinkController : public APlayerController
{
	GENERATED_BODY()

public:
	FHitResult GetSightRayHitResult() const;

private:
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	FHitResult GetLookVectorHitResult(FVector LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength = 700.0f;

};
