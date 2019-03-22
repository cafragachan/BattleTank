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

	float RadarRadius = 3000;

	UTankAimingComponent* AimingComp = nullptr;
	
};
