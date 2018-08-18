// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_TankPLayerControl.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API APC_TankPLayerControl : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank * GetControlledTank() const;

	void BeginPlay() override;


	
	
	
};
