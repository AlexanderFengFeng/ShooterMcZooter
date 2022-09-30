// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

UCLASS()
class SHOOTERMCZOOTER_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AShooterMcZooterGameModeBase* GameMode;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AActor> ActorClass;
	FTimerHandle SpawnTimerControllingRateIncrease;
	FTimerHandle SpawnTimer;

	float InitialSpawnDelayMinValue = 5.f;
	float InitialSpawnDelayMaxValue = 10.f;

	float DecreaseInDelayPerIteration = 1.f;
	float MinimumLoopingDelay = 5.f;

	float InitialSpawnDelay = 15.f;
	float SpawnDelay = InitialSpawnDelay;

	void Spawn();
	void SpawnDelegateWithIncreasingRateInfinitely();
};
