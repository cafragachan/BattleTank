// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		virtual void SetPawn(APawn* Pawn_) override;

		UFUNCTION()
		void OnTankDeath();

		UTankAimingComponent* AimingComp = nullptr;

public:

	float LineTraceRange = 1000000;


	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.3333f;


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitPos_) const;
};
