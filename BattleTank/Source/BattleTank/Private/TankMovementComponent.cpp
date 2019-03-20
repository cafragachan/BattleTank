// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"



void UTankMovementComponent::IntendMoveForward(float Forward_) 
{
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *GetOwner()->GetName(), Forward_);

}
