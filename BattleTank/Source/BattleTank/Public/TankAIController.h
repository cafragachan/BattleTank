// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* Pawn_) override;

	UFUNCTION()
	void OnTankDeath();

	UPROPERTY(EditAnywhere, Category = "Setup")
	float RadarRadius = 1000;

	UTankAimingComponent* AimingComp = nullptr;
	
};
