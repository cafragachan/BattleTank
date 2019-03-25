// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class ASpringWheel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathHandler);

UCLASS(Blueprintable)
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//returns currentHealth between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FDeathHandler DeathManager;


private:

	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere)
	int32 StartingHealth = 100.f;

	UPROPERTY(EditAnywhere)
	int32 CurrentHealth = StartingHealth;

	UPROPERTY(VisibleAnywhere)
		ASpringWheel* SprungWheel = nullptr;
};