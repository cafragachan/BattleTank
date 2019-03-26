// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	//
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
	
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASpringWheel::OnHit);

	if (GetAttachParentActor())
	{
		auto TankPrimitive = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		SpringConstraint->SetConstrainedComponents(TankPrimitive, NAME_None, Axle, NAME_None);
		AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}

}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tick test"));
		CurrentForceMagnitude = 0;
	}
}

void ASpringWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASpringWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentForceMagnitude += ForceMagnitude;
}

void ASpringWheel::ResetForce()
{
	CurrentForceMagnitude = 0;
}

void ASpringWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector()*CurrentForceMagnitude);
}



