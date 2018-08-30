// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UTankAimingComponent::aim(FVector HitLocation,float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}
	FVector OutLaunchSpeed;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	TArray< AActor*> ActorsToIgnore;

	bool bSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchSpeed,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		.0f,
		.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bSolutionFound)
	{
		auto AimDirection = OutLaunchSpeed.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s: aiming at %s, from a barrel at %s"), *TankName, *AimDirection.ToString(), *(BarrelLocation.ToString()))
		MoveBarrel(AimDirection);
		//rotate turret to correct z rotation
		//rotate barrel to correct y rotation
	}
	else 
	{
		UE_LOG(LogTemp,Warning,TEXT("NO AIM SOLUTION"))
		

	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5);

}


