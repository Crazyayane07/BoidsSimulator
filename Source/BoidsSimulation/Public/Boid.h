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
	float MaxSpeed = 4;

	void SetUp(const float &NewAllignPerception, const float &NewCohesionPerception, const float &NewSeparationPerception, const float &NewObstaclePerception);

	void UpdateMovement(const float &DeltaTime);

	void Flock(const TArray<ABoid*> &Boids, const TArray<AObstacle*> &Obstacles,const float &AllignMultiplayer,const float &CohesionMultiplayer,const float &SeparationMultiplayer, const float &ObstacleSeparationMultiplayer);

	void KeepInBoundaries(const float &X,const float &Y,const float &Z,const FVector &Center);

protected:
	virtual void BeginPlay() override;

	float AllignPerception;

	float CohesionPerception;

	float SeparationPerception;

	float ObstaclePerception;
	
	FVector GetAlignVector(const TArray<ABoid*> &Boids);

	FVector GetCohesionVector(const TArray<ABoid*> &Boids);
	
	FVector GetSeparationVector(const TArray<ABoid*> &Boids);

	FVector GetSeparationVectorForObstacles(const TArray<AObstacle*> &Obstacles);

	//only adds acceleration to velocity
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void Accelerate(const float &DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void DebugDraw(const FVector &AllignVector, const FVector &CohensionVector, const FVector &SeparationVector, const FVector &SeparationObstacleVector);
};
