// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class AObstacle;

UCLASS()
class BOIDSSIMULATION_API ABoid : public AActor
{
	GENERATED_BODY()

public:	
	ABoid();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxForce = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinDotProduct = 0.6;

	void SetUp(float NewPerception);

	void UpdateMovement();

	void Flock(const TArray<ABoid*> Boids, const TArray<AObstacle*> Obstacles, float AllignMultiplayer, float CohesionMultiplayer, float SeparationMultiplayer);

	void KeepInBoundaries(float X, float Y, float Z, FVector Center);

protected:
	virtual void BeginPlay() override;

	float Perception;
	
	FVector GetAlignVector(const TArray<ABoid*> Boids);

	FVector GetCohesionVector(const TArray<ABoid*> Boids);
	
	FVector GetSeparationVector(const TArray<ABoid*> Boids);

	FVector GetSeparationVectorForObstacles(const TArray<AObstacle*> Obstacles);

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void Accelerate();
};
