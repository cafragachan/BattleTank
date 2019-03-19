// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = Speed * MaxdegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	RawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));

}
