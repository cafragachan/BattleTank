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
	Barrel = FindComponentByClass<UTankBarrel>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{	
	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeSeconds;
	if (!ensure(Barrel)) return;

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



