// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid.h"
#include "Obstacle.h"
#include "..\Public\Boid.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoid::BeginPlay()
{
	Super::BeginPlay();
}

FVector ABoid::GetAlignVector(const TArray<ABoid*> &Boids)
{
	FVector AvgVector = FVector(0, 0, 0);
	int total = 0;

	if (Boids.Num() <= 0) return AvgVector;

	for (int i = 0; i < Boids.Num(); i++) 
	{
		float dist = FVector::Dist(GetActorLocation(), Boids[i]->GetActorLocation());
		
		if (Boids[i] != this && dist < Perception)
		{
			AvgVector = AvgVector + Boids[i]->Velocity;
			total++;
		}
	}

	if (total <= 0) return AvgVector;

	AvgVector = AvgVector / total;
	AvgVector.Normalize();
	AvgVector = AvgVector * MaxSpeed;
	AvgVector = AvgVector - Velocity;
	AvgVector.Normalize();

	return AvgVector;
}

FVector ABoid::GetCohesionVector(const TArray<ABoid*> &Boids)
{
	FVector AvgVector = FVector(0, 0, 0);
	int total = 0;

	if (Boids.Num() <= 0) return AvgVector;

	for (int i = 0; i < Boids.Num(); i++)
	{
		float Dist = FVector::Dist(GetActorLocation(), Boids[i]->GetActorLocation());

		FVector NormalizedVelocity = Velocity;
		NormalizedVelocity.Normalize();
		FVector NormalizeDistVector = Boids[i]->GetActorLocation() - GetActorLocation();
		NormalizeDistVector.Normalize();

		float DotProduct = FVector::DotProduct(NormalizedVelocity, NormalizeDistVector);

		if (Boids[i] != this && Dist < Perception)// && DotProduct > MinDotProduct)
		{
			AvgVector = AvgVector + Boids[i]->GetActorLocation();
			total++;
		}
	}

	if (total <= 0) return AvgVector;

	AvgVector = AvgVector / total;
	AvgVector = AvgVector - GetActorLocation();
	AvgVector.Normalize();
	AvgVector = AvgVector * MaxSpeed;
	AvgVector = AvgVector - Velocity;
	AvgVector.Normalize();

	return AvgVector;
}

FVector ABoid::GetSeparationVector(const TArray<ABoid*> &Boids)
{
	FVector AvgVector = FVector(0, 0, 0);
	int total = 0;

	if (Boids.Num() <= 0) return AvgVector;

	for (int i = 0; i < Boids.Num(); i++)
	{
		float dist = FVector::Dist(GetActorLocation(), Boids[i]->GetActorLocation());

		if (Boids[i] != this && dist < Perception)
		{
			FVector DiffVector = GetActorLocation() - Boids[i]->GetActorLocation();
			DiffVector = DiffVector / dist;

			AvgVector = AvgVector + DiffVector;
			total++;
		}
	}

	if (total <= 0) return AvgVector;

	AvgVector = AvgVector / total;
	AvgVector.Normalize();
	AvgVector = AvgVector * MaxSpeed;
	AvgVector = AvgVector - Velocity;
	AvgVector.Normalize();

	return AvgVector;
}

FVector ABoid::GetSeparationVectorForObstacles(const TArray<AObstacle*> &Obstacles)
{
	FVector AvgVector = FVector(0, 0, 0);
	int total = 0;

	for (int i = 0; i < Obstacles.Num(); i++)
	{
		float dist = FVector::Dist(GetActorLocation(), Obstacles[i]->GetActorLocation());

		if (dist < Perception*2)
		{
			FVector DiffVector = GetActorLocation() - Obstacles[i]->GetActorLocation();
			DiffVector = DiffVector / dist;

			AvgVector = AvgVector + DiffVector;
			total++;
		}
	}

	if (total <= 0) return AvgVector;

	AvgVector = AvgVector / total;
	AvgVector.Normalize();
	AvgVector = AvgVector * MaxSpeed;
	AvgVector = AvgVector - Velocity;
	AvgVector.Normalize();
	
	return AvgVector;
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoid::SetUp(const float &NewPerception)
{
	Perception = NewPerception;
}

void ABoid::UpdateMovement()
{
	SetActorLocation(GetActorLocation() + Velocity);
	Accelerate();

	if (Velocity.Size() > MaxSpeed)
	{
		Velocity.Normalize();
		if (Velocity.IsNormalized())
		{
			Velocity = Velocity * MaxSpeed;
		}
	}

	Acceleration = FVector(0, 0, 0);
}

void ABoid::Flock(const TArray<ABoid*> &Boids, const TArray<AObstacle*> &Obstacles, const float &AllignMultiplayer, const float &CohesionMultiplayer, const float &SeparationMultiplayer)
{
	FVector AllignVector = (AllignMultiplayer * GetAlignVector(Boids));
	FVector CohensionVector = (CohesionMultiplayer * GetCohesionVector(Boids));
	FVector SeparationVector = (SeparationMultiplayer * GetSeparationVector(Boids));
	FVector SeparationObstacleVector = (10 * GetSeparationVectorForObstacles(Obstacles));

	Acceleration = Acceleration + SeparationObstacleVector;
	Acceleration = Acceleration + AllignVector;
	Acceleration = Acceleration + CohensionVector;
	Acceleration = Acceleration + SeparationVector;
	
	DebugDraw(AllignVector, CohensionVector, SeparationVector, SeparationObstacleVector);
}

void ABoid::KeepInBoundaries(const float &X, const float &Y, const float &Z, const FVector &Center)
{
	if (GetActorLocation().X > X) {
		SetActorLocation(Center);
	}
	if (GetActorLocation().X < -X) {
		SetActorLocation(Center);
	}
	if (GetActorLocation().Y > Y) {
		SetActorLocation(Center);
	}
	if (GetActorLocation().Y < -Y) {
		SetActorLocation(Center);
	}
	if (GetActorLocation().Z > Z) {
		SetActorLocation(Center);
	}
	if (GetActorLocation().Z < -Z) {
		SetActorLocation(Center);
	}
}
