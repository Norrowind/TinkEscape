// Norrowind. All rights reserved.

#include "Tink.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DroidMovementComponent.h"
#include "DroidBody.h"
#include "HoverComponent.h"

// Sets default values
ATink::ATink()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root Component"));
	DroidBody = CreateDefaultSubobject<UDroidBody>(TEXT("Droid Body"));
	DroidBody->SetupAttachment(RootComponent);
	DroidBody->SetNotifyRigidBodyCollision(true);

	AzimuthGimbal = CreateDefaultSubobject<USceneComponent>(TEXT("Azimuth Gimbal"));
	AzimuthGimbal->SetupAttachment(DroidBody);
	AzimuthGimbal->SetRelativeLocation(SpringArmLocation);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(AzimuthGimbal);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DroidMovementComponent = CreateDefaultSubobject<UDroidMovementComponent>(TEXT("MovingComponent"));
	

}

// Called when the game starts or when spawned
void ATink::BeginPlay()
{
	Super::BeginPlay();

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

void ATink::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
	if (!ensure(SpringArm)) { return; }
	SpringArm->AddLocalRotation(FRotator(CameraInput.Y, 0.0f, 0.0f));
}

void ATink::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
	if (!ensure(DroidBody)) { return; }
	DroidBody->AddLocalRotation(FRotator(0.0f, CameraInput.X, 0.0f));
}
