// Norrowind. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tink.generated.h"

//Forward declaration
class USpringArmComponent;
class UCameraComponent;


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

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UCameraComponent* CameraComponent = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Functions to handle input
	void CameraPitch(float AxisValue);
	void CameraYaw(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;

	//Component Parametrs
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector SpringArmLocation = FVector(0.0f, 0.0f, 50.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FRotator SpringArmRotation = FRotator(-60.f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SpringArmLength = 400.0f;

};
