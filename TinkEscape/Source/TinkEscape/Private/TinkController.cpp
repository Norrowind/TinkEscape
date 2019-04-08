// Fill out your copyright notice in the Description page of Project Settings.

#include "TinkController.h"
#include "Classes/Engine/World.h"

//Get hit result of linetrace throurght crosshair
FHitResult ATinkController::GetSightRayHitResult() const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//Screen position of the crosshair to the world direction
	FVector OutLookDirection;
	if (GetLookDirection(ScreenLocation, OutLookDirection))
	{
		return GetLookVectorHitResult(OutLookDirection);
	}
	return FHitResult();
}


bool ATinkController::GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	);
	
}

FHitResult ATinkController::GetLookVectorHitResult(FVector LookDirection) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceLength);
	FHitResult OutHitResult;
	GetWorld()->LineTraceSingleByChannel
	(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera
	);
	return OutHitResult;
}

