// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAim = CreateDefaultSubobject<UTankAimingComponent>(FName("TankAimingComponent"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation_)
{
	TankAim->AimAt(HitLocation_, LaunchSpeed);

}

void ATank::Fire()
{	
	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeSeconds;

	if (Barrel && isReloaded)
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

void ATank::SetBarrelReference(UTankBarrel * Barrel_, UTankTurret * Turret_)
{
	if (!Barrel_ || !Turret_) return;
	Barrel = Barrel_;
	TankAim->SetBarrelComponent(Barrel_);
	TankAim->SetTurretComponent(Turret_);
}



