// Norrowind. All rights reserved.

#include "Tink.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ATink::ATink()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(SpringArmLocation, SpringArmRotation);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bEnableCameraLag = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ATink::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotate Tick with camera moving
	FRotator NewTinkRotation = GetActorRotation();
	NewTinkRotation.Yaw += CameraInput.X;
	SetActorRotation(NewTinkRotation);

	//Rotate camera pitch with spring arm
	if (!ensure(SpringArm)) { return; }
	else
	{
		FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
		NewSpringArmRotation.Pitch += CameraInput.Y;
		SpringArm->SetWorldRotation(NewSpringArmRotation);
	}

	//Handle movement based on axes
	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 400.0f;
		FVector NewTinkLocation = GetActorLocation();
		NewTinkLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewTinkLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewTinkLocation);
	}
}

// Called to bind functionality to input
void ATink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ATink::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ATink::CameraYaw);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATink::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATink::MoveRight);
}

void ATink::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ATink::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ATink::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void ATink::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

