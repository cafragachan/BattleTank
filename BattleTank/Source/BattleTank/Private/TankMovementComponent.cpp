// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::IntendMoveForward(float Speed_)
{
	if(!ensure(LeftTrack && RightTrack)) return;

	LeftTrack->SetThrottle(Speed_);
	RightTrack->SetThrottle(Speed_);
}

void UTankMovementComponent::IntendMoveRight(float Speed_)
{
	if (!ensure(LeftTrack && RightTrack)) return;

	LeftTrack->SetThrottle(Speed_);
	RightTrack->SetThrottle(-Speed_);
}

void UTankMovementComponent::IntendMoveLeft(float Speed_)
{
	if (!ensure(LeftTrack && RightTrack)) return;

	LeftTrack->SetThrottle(-Speed_);
	RightTrack->SetThrottle(Speed_);
}

void UTankMovementComponent::InitialiseMovement(UTankTrack * RightTrack_, UTankTrack * LeftTrack_)
{
	RightTrack = RightTrack_;
	LeftTrack = LeftTrack_;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto AISpeed = FVector::DotProduct(TankForward, AIForwardIntention);
	auto AIRotation = FVector::CrossProduct(TankForward, AIForwardIntention);

	IntendMoveForward(AISpeed);
	if (AIRotation.Z > 0) IntendMoveRight(AIRotation.Size());
	else if (AIRotation.Z < 0) IntendMoveLeft(AIRotation.Size());


}
