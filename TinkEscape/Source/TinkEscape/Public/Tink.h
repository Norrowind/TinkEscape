// Norrowind. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tink.generated.h"

//Forward declaration
class USpringArmComponent;
class UCameraComponent;
class UDroidMovementComponent;
class UDroidBody;
class UStaticMeshComponent;

UCLASS()
class TINKESCAPE_API ATink : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATink();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UDroidMovementComponent* DroidMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UDroidBody* DroidBody = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* DroidAppearance = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Functions to camera input
	void CameraPitch(float AxisValue);
	void CameraYaw(float AxisValue);
	void RotateCameraPitch();
	void RotateTinkWithCamera();

	//Input variable
	FVector2D CameraInput;

	//Component Parametrs
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector SpringArmLocation = FVector(0.0f, 0.0f, 50.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FRotator SpringArmRotation = FRotator(-60.f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SpringArmLength = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinSpringArmPitch = -80.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxSpringArmPitch = -15.0f;
};
