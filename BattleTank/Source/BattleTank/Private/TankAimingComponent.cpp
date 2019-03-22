// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"



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

	Barrel = GetOwner()->FindComponentByClass<UTankBarrel>();
	Turret = GetOwner()->FindComponentByClass<UTankTurret>();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UTankAimingComponent::AimAt(FVector Target_)
{
	if (!ensure(Barrel)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("DONKEY: not barrel"));
		return; 
	}

	FVector OutVel;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStartPosition"));

	if (UGameplayStatics::SuggestProjectileVelocity
			(
				this, OutVel, 
				StartLocation, 
				Target_, 
				LaunchSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace
			)
		)
	{
		auto AimDirection = OutVel.GetSafeNormal().Rotation();

		MoveBarrel(AimDirection);
	}

}


void UTankAimingComponent::InitialiseAim(UTankTurret * Turret_, UTankBarrel * Barrel_)
{
	Barrel = Barrel_;
	Turret = Turret_;
}

void UTankAimingComponent::MoveBarrel(FRotator Direction)
{
	if (!ensure(Barrel && Turret)) return;
	auto DeltaElevation = Direction - Barrel->GetForwardVector().Rotation();
	auto DeltaTurretRotation = Direction - Turret->GetForwardVector().Rotation();

	Barrel->Elevate(DeltaElevation.Pitch);
	Turret->Rotate(DeltaTurretRotation.Yaw);

}

