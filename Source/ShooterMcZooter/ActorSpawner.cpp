// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
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
	float InFirstDelay = FMath::FRandRange(5.f, 10.f);
	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AActorSpawner::Spawn,
		SpawnRate,
		true,
		InFirstDelay);
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorSpawner::Spawn()
{
	GetWorld()->SpawnActor<AActor>(
		ActorClass,GetActorLocation(),
		FRotator(0.f,UKismetMathLibrary::RandomRotator().Yaw, 0.f));
}
