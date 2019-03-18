// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledAITank = GetControlledTank();
	auto TargetTank = GetPlayerTank();

	if (ControlledAITank && TargetTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: is AI possesed and is targeting %s"), *ControlledAITank->GetName(), *TargetTank->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank or player tank returning NULL"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto Player = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());


	return Player->GetControlledTank();
}

void ATankAIController::AimTowardsPlayer()
{
	if (!GetControlledTank()) return;

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
