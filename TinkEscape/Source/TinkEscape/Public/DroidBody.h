// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DroidBody.generated.h"

/**
 * Component which represnts physics body of droid, which actualy is anti-gravity pillow
 */

class UHoverComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class TINKESCAPE_API UDroidBody : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UDroidBody();

	//Set input moving between 1 and -1;
	void SetDirectInputMovement(float Throw);
	void SetSideInputMovement(float Throw);

private:

	void MoveForward(float DrivingForce);
	void MoveRight(float DrivingForce);
	
	UFUNCTION()
	void OnHover();

	UFUNCTION()
	void OnAir();

	virtual void BeginPlay() override;
	
	//Driving force in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float DrivingForce = 2500000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AirDrivingForce = 100000.0f;

	//Input variable
	FVector2D InputMovement;

	UHoverComponent* HoverComponent = nullptr;


	
};
