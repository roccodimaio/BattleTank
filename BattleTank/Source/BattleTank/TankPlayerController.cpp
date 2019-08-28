// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"
#include "Engine/EngineTypes.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No TankPlayerController on %s !"), *(GetOwner()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s !"), *(ControlledTank->GetName()));
	}

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; //Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}


}

// Get world location of linetrace through crosshair, return true if it hits landscape

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//OutHitLocation = FVector(1.0f, 1.0f, 1.0f);

	// Find the cross hair position
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s "), *ScreenLocation.ToString());
	

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		// GetVectorHitLocation(); 
		GetLookVectorHitLocation(LookDirection, OutHitLocation); 

		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s "), *LookDirection.ToString());
	}

	
	return true;
}


// De-Project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); 
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f, 0.0f, 0.0f);
	return false; 
}


