// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move barrel the right amount this frame

	// Given a max elevation speed, and frame time

	auto Time = GetWorld()->GetTimeSeconds(); 
	UE_LOG(LogTemp, Warning, TEXT("%f:  Barrel->Elevate() called @ %f"), Time, RelativeSpeed);
}