// Norrowind. All rights reserved.

#include "Tink.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DroidMovementComponent.h"
#include "DroidBody.h"

// Sets default values
ATink::ATink()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DroidBody = CreateDefaultSubobject<UDroidBody>(TEXT("Droid Body"));
	SetRootComponent(DroidBody);
	DroidBody->SetNotifyRigidBodyCollision(true);

	DroidAppearance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tink"));
	DroidAppearance->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(DroidAppearance);
	SpringArm->SetRelativeLocationAndRotation(SpringArmLocation, SpringArmRotation);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DroidMovementComponent = CreateDefaultSubobject<UDroidMovementComponent>(TEXT("MovingComponent"));
}


void ATink::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ATink::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
}

// Called to bind functionality to input
void ATink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraPitch", this, &ATink::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ATink::CameraYaw);
	PlayerInputComponent->BindAxis("MoveForward", DroidMovementComponent, &UDroidMovementComponent::IntendMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", DroidMovementComponent, &UDroidMovementComponent::IntendMoveRight);
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

	RotateCameraPitch();
	RotateTinkWithCamera();

}

//Rotate camera pitch with spring arm, but limit it
void ATink::RotateCameraPitch()
{
	if (!ensure(SpringArm)) { return; }
	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch + CameraInput.Y, MinSpringArmPitch, MaxSpringArmPitch);
	SpringArm->SetWorldRotation(NewSpringArmRotation);

}

void ATink::RotateTinkWithCamera()
{	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

}







