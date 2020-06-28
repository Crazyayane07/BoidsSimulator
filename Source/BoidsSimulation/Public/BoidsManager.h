// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidsManager.generated.h"

class ABoid;

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
	TSubclassOf<class ABoid> BoidClassToSpawn;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	FVector GetSpawnPosition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")
	float BoidPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float AllignMultiplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float CohesionMultiplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float SeparationMultiplayer;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boids")
	void OnFinishedSpawningBoids();

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
