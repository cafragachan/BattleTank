// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathMortarHandler);

UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMortar();

	//returns currentHealth between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FDeathMortarHandler DeathManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere)
		int32 StartingHealth = 100.f;

	UPROPERTY(EditAnywhere)
		int32 CurrentHealth;
	
};
