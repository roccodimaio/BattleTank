// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
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

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return; 
	}

	// Get world location if linetrace through crosshair
	// if it hits the landscape
		// Tell controlled tank to aim at this point
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); 
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}