// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_TankPLayerControl.generated.h"

/**
 * 
 */
class ATank;
UCLASS()
class BATTLE_TANK_API APC_TankPLayerControl : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	
private:
	ATank * GetControlledTank() const;

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector &OutHitLocation, FVector CameraWorldRotation) const;


};
