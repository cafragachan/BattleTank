// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"


class USphereComponent;

UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* AxleConstraint = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ResetForce();

	void ApplyForce();

	float CurrentForceMagnitude = 0;
};
