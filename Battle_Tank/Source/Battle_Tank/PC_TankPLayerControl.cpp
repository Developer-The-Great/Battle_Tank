// Fill out your copyright notice in the Description page of Project Settings.
#include "PC_TankPLayerControl.h"
#include "Tank.h"
#include "Battle_Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"




void APC_TankPLayerControl::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("begin play!"))
	auto* ControlledTank = GetControlledTank();
	Super::BeginPlay();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller: no tank has been possesed"))

	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller: %s has been possesed"),*(ControlledTank->GetName()))
	}
	
}
//tick
void APC_TankPLayerControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}


ATank*APC_TankPLayerControl::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
} 
void APC_TankPLayerControl::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	//RayCast Through dot
	if (GetSightRayHitLocation(HitLocation)) 
	{
		//aim towards crosshair
		
		GetControlledTank()->AimAt(HitLocation);
		
	}
	
}

bool APC_TankPLayerControl::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	// de project screen position to world direction
	//line trace on that direction
	FVector OUTCameraWorldPosition;
	FVector OUTCameraWorldRotation;
	
	
	if (DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUTCameraWorldPosition,
		OUTCameraWorldRotation
	))
	{

		return GetLookVectorHitLocation(OutHitLocation, OUTCameraWorldRotation);
	}
	
		return false;
	

	
}
bool APC_TankPLayerControl::GetLookVectorHitLocation(FVector &OutHitLocation, FVector CameraWorldDirection) const
{
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (CameraWorldDirection * LineTraceRange);

	bool bLineTraceHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation,ECollisionChannel::ECC_Visibility);
	
	if(bLineTraceHit)
	{
		OutHitLocation = Hit.Location;
		return true;
	}
	
		return false;
	
	

	
}
	



