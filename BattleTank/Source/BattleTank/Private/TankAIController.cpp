// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawn();

	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, RadarRadius);
		AimingComp->AimAt(PlayerTank->GetActorLocation());
		//ControlledTank->Fire();
	}
}


	

