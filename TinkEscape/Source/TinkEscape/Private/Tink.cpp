// Norrowind. All rights reserved.

#include "Tink.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DroidMovementComponent.h"
#include "DroidBody.h"
#include "BuildingComponent.h"


// Sets default values
ATink::ATink()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	BuildingComponent = CreateDefaultSubobject<UBuildingComponent>(TEXT("BuildingComponent"));

}

// Called when the game starts or when spawned
void ATink::BeginPlay()
{
	Super::BeginPlay();
	KineticEnergy = StartingKineticEnergy;
	BuildingEnergy = StartingBuildingEnergy;
}

void ATink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Always restore kinetick energy
	KineticEnergy = FMath::Clamp(KineticEnergy + (KineticEnergyRestorePerSecond * DeltaTime), 0.0f, StartingKineticEnergy);

}

void ATink::SetKinetickEnergyExpend(float KinetickEnergyExpand)
{
	KineticEnergy -= KinetickEnergyExpand;
}

float ATink::GetBuildingEnergyPercent() const
{
	return (float)BuildingEnergy / (float)StartingBuildingEnergy;
}

int32 ATink::GetBuildingEnergy() const
{
	return BuildingEnergy;
}

void ATink::SetBuildingEnergyExpend(int32 BuildingEnergyExpand)
{
	BuildingEnergy -= BuildingEnergyExpand;
}

float ATink::GetKineticEnergyPercent() const
{
	return KineticEnergy / StartingKineticEnergy;
}

float ATink::GetKineticEnergy() const
{
	return KineticEnergy;
}

// Called to bind functionality to input
void ATink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraPitch", this, &ATink::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ATink::CameraYaw);
	PlayerInputComponent->BindAxis("MoveForward", DroidMovementComponent, &UDroidMovementComponent::IntendMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", DroidMovementComponent, &UDroidMovementComponent::IntendMoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, DroidMovementComponent, &UDroidMovementComponent::PowerUpJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, DroidMovementComponent, &UDroidMovementComponent::StartJump);
	PlayerInputComponent->BindAction("GunAction", IE_Pressed, this, &ATink::GunPressed);
	PlayerInputComponent->BindAction("GunAction", IE_Released, this, &ATink::GunReleased);
	PlayerInputComponent->BindAction("GunAlternativeAction", IE_Pressed, this, &ATink::GunAlternativeAction);
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

void ATink::GunPressed()
{
	BuildingComponent->PlaceGhostPlatform();
}

void ATink::GunReleased()
{
	BuildingComponent->PlatformBuildShot();
}

void ATink::GunAlternativeAction()
{
	BuildingComponent->ComsumePlatformShot();
}
