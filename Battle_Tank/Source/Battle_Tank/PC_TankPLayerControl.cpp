// Fill out your copyright notice in the Description page of Project Settings.
#include "PC_TankPLayerControl.h"
#include "Battle_Tank.h"



ATank*APC_TankPLayerControl::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}
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



