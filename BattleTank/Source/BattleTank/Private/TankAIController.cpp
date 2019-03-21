// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, RadarRadius);
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}


	

