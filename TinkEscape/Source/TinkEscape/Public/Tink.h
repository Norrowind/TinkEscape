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
	USceneComponent* AzimuthGimbal = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetKinetickEnergyExpend(float KinetickEnergyExpand);

	UFUNCTION(BlueprintPure, Category = "Setup")
	float GetKineticEnergyPercent();

	int32 GetKineticEnergy();

private:
	//Functions to camera input
	void CameraPitch(float AxisValue);
	void CameraYaw(float AxisValue);

	//Input variable
	FVector2D CameraInput;

	//Component default Parametrs
	FVector SpringArmLocation = FVector(0.0f, 0.0f, 50.0f);
	float SpringArmLength = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kinetic Energy")
	int32 KineticEnergyRestorePerSecond = 5;

	//Energy which Tink uses for jumps and kinetic gun, initialize in begin play
	int32 KineticEnergy;
	int32 StartingKineticEnergy = 100;
};
