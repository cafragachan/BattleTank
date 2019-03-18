// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class ATank;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.3333f;

	float LineTraceRange = 1000000;

	ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitPos_) const;
};
