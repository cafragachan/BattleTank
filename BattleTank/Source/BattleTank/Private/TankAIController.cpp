// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"
#include "Mortar.h"


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
		if(AimingComp->GetFiringState() == EFiringState::Locked) AimingComp->Fire();
	}
}

void ATankAIController::SetPawn(APawn * Pawn_)
{
	Super::SetPawn(Pawn_);

	if (Pawn_)
	{
		auto PossessedTank = Cast<ATank>(Pawn_);
		auto PossessedMortar = Cast<AMortar>(Pawn_);

		if (PossessedTank) 
		{
			PossessedTank->DeathManager.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		}
		if (PossessedMortar)
		{
			PossessedMortar->DeathManager.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		}

	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI tank got destroyed"));
	if (!GetPawn()) return;
	GetPawn()->DetachFromControllerPendingDestroy();
}


	

