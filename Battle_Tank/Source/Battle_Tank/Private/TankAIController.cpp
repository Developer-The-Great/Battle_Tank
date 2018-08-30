// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ProtectPointer();
	

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetAIControlledTank())
	{
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	
	}
	

}

void ATankAIController::ProtectPointer()
{
	auto ControlledAITank = GetAIControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!ControlledAITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller:no tank has been possessed!"))
			return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller: tank %s"), *(ControlledAITank->GetName()))
	}
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller:Player Tank not found!"))
			return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller: tank %s is the player"), *(PlayerTank->GetName()))
	}
}

