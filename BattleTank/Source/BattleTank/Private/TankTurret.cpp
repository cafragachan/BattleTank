// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine.h"
#include "Components/SceneComponent.h"



void UTankTurret::Rotate(float RelativeSpeed_)
{
	auto Speed = FMath::Clamp<float>(RelativeSpeed_, -1, 1);

	auto RotationChange = Speed * MaxdegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	auto RotatorString = FRotator(0, RawNewRotation, 0).ToString();
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}

