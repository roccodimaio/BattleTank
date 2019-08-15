// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const; 

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override; 
		
	// Start the tank moving the barrel so that a shot would hit where
	// teh crosshair intersects the world
	virtual void AimTowardsCrosshair();

	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;


	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f; 

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f; 

	
};
