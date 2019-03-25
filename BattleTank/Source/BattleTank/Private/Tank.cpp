// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	int32 ActualDamage = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(ActualDamage, 0, CurrentHealth);

	if (DamageToApply > 0.f)
	{
		CurrentHealth -= DamageToApply;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (CurrentHealth <= 0.f)
		{
			DeathManager.Broadcast();
			//SetLifeSpan(0.001f);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Actual Damage = %i, Damage to Apply = %i"), ActualDamage, DamageToApply);

	return ActualDamage;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::GetHealthPercentage()
{
	return (float)CurrentHealth / (float)StartingHealth;
}





