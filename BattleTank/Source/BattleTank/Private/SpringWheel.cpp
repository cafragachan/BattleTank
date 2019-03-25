// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(PhysicsConstraint);

}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));

		auto TankPrimitive = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		PhysicsConstraint->SetConstrainedComponents(TankPrimitive, NAME_None, Wheel, NAME_None);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

