// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid.h"
#include "..\Public\Boid.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoid::BeginPlay()
{
	Super::BeginPlay();
}

FVector ABoid::GetAlignVector(const TArray<ABoid*> Boids)
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

	AvgVector = AvgVector / total;

	AvgVector = AvgVector * MaxSpeed; // ?!?!?!?

	AvgVector = AvgVector - Velocity;

	if (AvgVector.Size() > MaxForce) // ?!?!?!?
	{
		AvgVector.Normalize();
		if (Acceleration.IsNormalized())
		{
			AvgVector = AvgVector * MaxForce;
		}
	}

	return AvgVector;
}

FVector ABoid::GetCohesionVector(const TArray<ABoid*> Boids)
{
	FVector AvgVector = FVector(0, 0, 0);
	int total = 0;

	if (Boids.Num() <= 0) return AvgVector;

	for (int i = 0; i < Boids.Num(); i++)
	{
		float dist = FVector::Dist(GetActorLocation(), Boids[i]->GetActorLocation());

		if (Boids[i] != this && dist < Perception)
		{
			AvgVector = AvgVector + Boids[i]->GetActorLocation();
			total++;
		}
	}

	AvgVector = AvgVector / total;
	AvgVector = AvgVector - GetActorLocation();
	AvgVector = AvgVector * MaxSpeed; // ?!?!?!?
	AvgVector = AvgVector - Velocity;

	if (AvgVector.Size() > MaxForce) // ?!??!?!?
	{
		AvgVector.Normalize();
		if (Acceleration.IsNormalized())
		{
			AvgVector = AvgVector * MaxForce;
		}
	}

	return AvgVector;
}

FVector ABoid::GetSeparationVector(const TArray<ABoid*> Boids)
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

	AvgVector = AvgVector / total;
	AvgVector = AvgVector * MaxSpeed; // ?!?!?!?
	AvgVector = AvgVector - Velocity;

	if (AvgVector.Size() > MaxForce) // ?!??!?!?
	{
		AvgVector.Normalize();
		if (Acceleration.IsNormalized())
		{
			AvgVector = AvgVector * MaxForce;
		}
	}

	return AvgVector;
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoid::SetUp(float NewPerception) 
{
	Perception = NewPerception;
}

void ABoid::UpdateMovement()
{
	SetActorLocation(GetActorLocation() + Velocity);
	Accelerate();

	if (Velocity.Size() > MaxSpeed) // ?!??!?!?
	{
		Velocity.Normalize();
		if (Velocity.IsNormalized())
		{
			Velocity = Velocity * MaxSpeed;
		}
	}

	Acceleration = FVector(0, 0, 0);
}

void ABoid::Flock(const TArray<ABoid*> Boids, float AllignMultiplayer, float CohesionMultiplayer, float SeparationMultiplayer)
{
	Acceleration = Acceleration + (AllignMultiplayer * GetAlignVector(Boids));
	Acceleration = Acceleration + (CohesionMultiplayer * GetCohesionVector(Boids));
	Acceleration = Acceleration + (SeparationMultiplayer * GetSeparationVector(Boids));
}

void ABoid::KeepInBoundaries(float X, float Y, float Z, FVector Center)
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
