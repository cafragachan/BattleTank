// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


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

	
}

void UTankAimingComponent::AimAt(FVector Target_, float LaunchSpeed_)
{
	if (!Barrel) return;

	FVector OutVel;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStartPosition"));

	if (UGameplayStatics::SuggestProjectileVelocity
			(
				this, OutVel, 
				StartLocation, 
				Target_, 
				LaunchSpeed_,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace
			)
		)
	{
		auto AimDirection = OutVel.GetSafeNormal().ToString();

		UE_LOG(LogTemp, Warning, TEXT("aim direction: %s"), *AimDirection);
	}

}

void UTankAimingComponent::SetBarrelComponent(UStaticMeshComponent * Barrel_)
{
	Barrel = Barrel_;
}

