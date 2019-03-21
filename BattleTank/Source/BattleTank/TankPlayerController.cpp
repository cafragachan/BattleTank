// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComp = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComp) FoundAimingComponent(AimingComp);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) return;

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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

		FCollisionQueryParams Param = FCollisionQueryParams(FName(NAME_None), false, GetControlledTank());

		//GetWorld()->LineTraceSingleByObjectType(Hit, GetControlledTank()->GetActorLocation(), EndPos, ECollisionChannel::ECC_PhysicsBody, Param);
		GetWorld()->LineTraceSingleByChannel(
			Hit, 
			CameraPos,
			EndPos, 
			ECollisionChannel::ECC_Visibility,
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

