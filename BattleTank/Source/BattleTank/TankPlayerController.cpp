// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{

	PossesedTank = Cast<ATank>(GetPawn());

	if (PossesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: controlled pawn"), *PossesedTank->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO controlled pawn"), *GetPawn()->GetName());

	}
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

