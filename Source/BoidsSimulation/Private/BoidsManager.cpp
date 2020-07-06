// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidsManager.h"
#include "Boid.h"
#include "..\Public\BoidsManager.h"

ABoidsManager::ABoidsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoidsManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < NumbeOfBoidsToSpawn; i++)
	{
		FActorSpawnParameters SpawnInfo;

		ABoid* NewBoid = GetWorld()->SpawnActor<ABoid>(BoidClassToSpawn->GetDefaultObject()->GetClass(), GetSpawnPosition(), FRotator(0,0,0), SpawnInfo);
		NewBoid->SetUp(BoidAllignPerception, BoidCohesionPerception, BoidSeparationPerception, BoidObstaclePerception);

		Boids.Add(NewBoid);
	}

	OnFinishedSpawningBoids();
}

void ABoidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < Boids.Num(); i++)
	{
		Boids[i]->Flock(Boids, Obstacles, AllignMultiplayer, CohesionMultiplayer, SeparationMultiplayer, ObstacleSeparationMultiplayer);
		Boids[i]->UpdateMovement();
	}
}

void ABoidsManager::ResetUpBoidsPerception(const float & NewAllignPerception, const float & NewCohesionPerception, const float & NewSeparationPerception, const float & NewObstaclePerception)
{
	for (int i = 0; i < Boids.Num(); i++)
	{
		Boids[i]->SetUp(NewAllignPerception, NewCohesionPerception, NewSeparationPerception, NewObstaclePerception);
	}
}

