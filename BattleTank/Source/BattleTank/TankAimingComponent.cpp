// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret) { return; }
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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(aimDirection);

		//old logging stuff
		//auto tankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *tankName, *aimDirection.ToString())
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	//get difference between current barrel rotation and aimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - BarrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}