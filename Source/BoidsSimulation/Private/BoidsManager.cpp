// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidsManager.h"
#include "Boid.h"

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
		NewBoid->SetUp(BoidPerception);

		Boids.Add(NewBoid);
	}

	OnFinishedSpawningBoids();
}

void ABoidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < Boids.Num(); i++)
	{
		Boids[i]->KeepInBoundaries(GetX(), GetY(), GetZ(), GetCenter());
		Boids[i]->Flock(Boids, AllignMultiplayer, CohesionMultiplayer, SeparationMultiplayer);
		Boids[i]->UpdateMovement();
	}
}

