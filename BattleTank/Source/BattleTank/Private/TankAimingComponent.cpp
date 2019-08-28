// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet; 
}

// Called when the game starts

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString(); 
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s !"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);


	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity(0.0f, 0.0f, 0.0f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
	bool bHaveAimSoultion = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
		 // Calculate the OutLaunchVelocity
	if (bHaveAimSoultion)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection); 
		auto TankName = GetOwner()->GetName(); 

		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s "),*TankName, *AimDirection.ToString());
	}

	// If no solution found do nothing
	
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	// Move barrel the right amount this frame

	// Given a max elevation speed, and frame time
}


