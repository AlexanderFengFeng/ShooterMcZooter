// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "ShooterMcZooterGameModeBase.h"
#include "TimerManager.h"


// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	GameMode = GetWorld()->GetAuthGameMode<AShooterMcZooterGameModeBase>();
	GetWorldTimerManager().SetTimer(
		SpawnTimerControllingRateIncrease,
		this,
		&AActorSpawner::SpawnDelegateWithIncreasingRateInfinitely,
		FMath::FRandRange(InitialSpawnDelayMinValue, InitialSpawnDelayMaxValue),
		false);
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameMode->IsGameEnding())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerControllingRateIncrease);
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void AActorSpawner::Spawn()
{
	GetWorld()->SpawnActor<AActor>(
		ActorClass,GetActorLocation(),
		FRotator(0.f,UKismetMathLibrary::RandomRotator().Yaw, 0.f));
}

void AActorSpawner::SpawnDelegateWithIncreasingRateInfinitely()
{
	Spawn();
	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AActorSpawner::SpawnDelegateWithIncreasingRateInfinitely,
		SpawnDelay);
	SpawnDelay = FMath::Max(MinimumLoopingDelay, SpawnDelay - DecreaseInDelayPerIteration);
}
