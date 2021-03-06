// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidsManager.generated.h"

class ABoid;
class AObstacle;

UCLASS()
class BOIDSSIMULATION_API ABoidsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoidsManager();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	int NumbeOfBoidsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	TArray<ABoid*> Boids;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	TArray<AObstacle*> Obstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	TSubclassOf<class ABoid> BoidClassToSpawn;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	FVector GetSpawnPosition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")
	float BoidAllignPerception = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")
	float BoidCohesionPerception = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")
	float BoidSeparationPerception = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")
	float BoidObstaclePerception = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float AllignMultiplayer = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float CohesionMultiplayer = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float SeparationMultiplayer = 1.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float ObstacleSeparationMultiplayer = 10;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	void OnFinishedSpawningBoids();

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void ResetUpBoidsPerception(const float &NewAllignPerception, const float &NewCohesionPerception, const float &NewSeparationPerception, const float &NewObstaclePerception);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	FVector GetCenter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	float GetX();

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	float GetY();

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	float GetZ();
};
