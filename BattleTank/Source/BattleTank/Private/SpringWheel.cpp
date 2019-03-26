// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/SphereComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(SpringConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));

		auto TankPrimitive = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		SpringConstraint->SetConstrainedComponents(TankPrimitive, NAME_None, Axle, NAME_None);
		AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
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

