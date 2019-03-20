// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHover);

class UDroidBody;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINKESCAPE_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();

	FOnHover OnHover;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UDroidBody* DroidBody = nullptr;
	void Hover();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TraceLength = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ForceToHover = 15000000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LinearHoverDamping = 18.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AngularHoverDamping = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float NormalLinearDamping = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float NormalAngularDamping = 0.6f;

		
};
