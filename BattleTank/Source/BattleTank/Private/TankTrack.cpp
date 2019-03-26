// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"
#include "SpringWheel.h"
#include "SpawnPoint.h"



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UTankTrack::SetThrottle(float Throttle_) 
{
	Throttle = FMath::Clamp<float>(Throttle_, -1, 1);
	DriveTrack();
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<ASpringWheel*> Wheels;
	TArray<USceneComponent*> SpawnSceneComponent;
	GetChildrenComponents(false, SpawnSceneComponent);


	for (USceneComponent* SpawnPoint : SpawnSceneComponent)
	{
		auto SP = Cast<USpawnPoint>(SpawnPoint);
		if (!SP) continue;
		Wheels.Add(SP->WheelAttached);
	}

	return Wheels;
}

void UTankTrack::DriveTrack()
{
	auto Wheels = GetWheels();

	for (ASpringWheel* Wheel : Wheels) {


		Wheel->AddDrivingForce(Throttle * TrackMaxDrivingForce / Wheels.Num());
	}
}


