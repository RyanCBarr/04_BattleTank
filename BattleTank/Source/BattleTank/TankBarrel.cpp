// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//move barrel the right amount this frame given max speed and frametime
	//elevate barrel to align socket with correct firing solution location

	UE_LOG(LogTemp, Warning, TEXT("Barrel-elevate called at speed: %f"), DegreesPerSecond)
}


