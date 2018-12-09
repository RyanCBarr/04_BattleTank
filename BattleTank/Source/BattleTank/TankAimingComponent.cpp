// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should this tick?

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//calculate outlaunch velocity	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		startLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f Firing Solution found"), time)

		//old logging stuff
		//auto tankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *tankName, *aimDirection.ToString())
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f No Aim solution found"), time)
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	//rotate turret to align socket with correct firing solution location

	//get difference between current barrel rotation and aimDirection
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(5.f);
	//Barrel->Elevate(5.f); //TODO remove magic number

}