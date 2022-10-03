// Fill out your copyright notice in the Description page of Project Settings.


#include "GetThemGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


AGetThemGameMode::AGetThemGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGetThemGameMode::BeginPlay()
{
    Super::BeginPlay();
}


void AGetThemGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!bGameIsEnding)
    {
        TimeLeft -= DeltaSeconds;
    }
    if (TimeLeft <= 0 && !bGameIsEnding)
    {
        EndGame(false);
    }
}


void AGetThemGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    if (bGameIsEnding) return;

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame(false);
    }
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AGetThemGameMode::EndGame(bool bIsPlayerWinner)
{
    Super::EndGame();
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}

int32 AGetThemGameMode::GetScore() const
{
    return FMath::CeilToInt32(TimeLeft);
}