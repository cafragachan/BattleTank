// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAim = FindComponentByClass<UTankAimingComponent>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation_)
{
	if (!ensure(TankAim)) return;
	TankAim->AimAt(HitLocation_, LaunchSpeed);

}

void ATank::Fire()
{	
	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeSeconds;
	if (!ensure(TankAim)) return;

	if (TankAim->Barrel && isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(ProjectileBP,
			TankAim->Barrel->GetSocketLocation(FName("ProjectileStartPosition")),
			TankAim->Barrel->GetSocketRotation(FName("ProjectileStartPosition"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}



