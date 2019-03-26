// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

class ASpringWheel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	ASpringWheel* WheelAttached = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Suspension = nullptr;
};
