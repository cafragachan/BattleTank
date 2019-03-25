// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComp) FoundAimingComponent(AimingComp);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * Pawn_)
{
	Super::SetPawn(Pawn_);

	if (Pawn_)
	{
		auto PossessedTank = Cast<ATank>(Pawn_);

		if (!ensure(PossessedTank)) return;

		PossessedTank->DeathManager.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("My tank got destroyed"));
	StartSpectatingOnly();

}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) return;

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComp->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitPos_) const
{
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);

	FVector2D ScreenLocation = FVector2D(ViewportX * CrosshairX, ViewportY * CrosshairY);

	FHitResult Hit;
	FVector WorldPos, Direction, EndPos;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPos, Direction)) 
	{
		FVector CameraPos = PlayerCameraManager->GetCameraLocation();
		EndPos = CameraPos + Direction * LineTraceRange;

		FCollisionQueryParams Param = FCollisionQueryParams(FName(NAME_None), false, GetPawn());

		//GetWorld()->LineTraceSingleByObjectType(Hit, GetControlledTank()->GetActorLocation(), EndPos, ECollisionChannel::ECC_PhysicsBody, Param);
		GetWorld()->LineTraceSingleByChannel(
			Hit, 
			CameraPos,
			EndPos, 
			ECollisionChannel::ECC_Camera,
			Param
			
		);

	}
		

	if (Hit.GetActor()) 
	{
		HitPos_ = Hit.Location;
		return true;
	}

	else { return false; }
}

