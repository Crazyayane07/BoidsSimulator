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
	AvgVector = AvgVector - Velocity;

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
	Velocity = Velocity + Acceleration;
}

void ABoid::Flock(const TArray<ABoid*> Boids)
{
	Acceleration = GetAlignVector(Boids);
}