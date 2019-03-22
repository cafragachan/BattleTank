// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->TimeSeconds;

	Barrel = GetOwner()->FindComponentByClass<UTankBarrel>();
	Turret = GetOwner()->FindComponentByClass<UTankTurret>();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((GetWorld()->TimeSeconds - LastFireTime) < ReloadTimeSeconds) { FiringState = EFiringState::Reloading; }
	else if(IsBarrelMoving()){ FiringState = EFiringState::Aiming; }
	else { FiringState = EFiringState::Locked; }
}

void UTankAimingComponent::AimAt(FVector Target_)
{
	if (!ensure(Barrel)) return; 

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
		AimDirection = OutVel.GetSafeNormal();

		MoveBarrel(AimDirection.Rotation());
	}

}


void UTankAimingComponent::InitialiseAim(UTankTurret * Turret_, UTankBarrel * Barrel_)
{
	Barrel = Barrel_;
	Turret = Turret_;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::MoveBarrel(FRotator Direction)
{
	if (!ensure(Barrel && Turret)) return;
	auto DeltaElevation = Direction - Barrel->GetForwardVector().Rotation();
	auto DeltaTurretRotation = Direction - Turret->GetForwardVector().Rotation();

	Barrel->Elevate(DeltaElevation.Pitch);

	if(FMath::Abs(DeltaTurretRotation.Yaw) <= 180) Turret->Rotate(DeltaTurretRotation.Yaw);
	else if (FMath::Abs(DeltaTurretRotation.Yaw) > 180) Turret->Rotate(-DeltaTurretRotation.Yaw);

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return true; }

	bool isMoving = true;

	if (Barrel->GetForwardVector().Equals(AimDirection, 0.01f)) { isMoving = false; }
	else { 	isMoving = true; }

	return isMoving;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) return;

	if (FiringState != EFiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(ProjectileBP,
				Barrel->GetSocketLocation(FName("ProjectileStartPosition")),
				Barrel->GetSocketRotation(FName("ProjectileStartPosition"))
				);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

