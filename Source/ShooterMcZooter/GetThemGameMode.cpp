// Fill out your copyright notice in the Description page of Project Settings.


#include "GetThemGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "ShooterGameInstance.h"


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
    if (TimeLeft <= 0)
    {
        EndGame(false);
    }
}


void AGetThemGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

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
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        if (bIsPlayerWinner)
        {
            UShooterGameInstance* GameInstance = Cast<UShooterGameInstance>(GetGameInstance());
            int32 TimeLeftInInt = FMath::FloorToInt32(TimeLeft);
            GameInstance->AddOrUpdateHighScore(HighScoreKey, TimeLeftInInt);
        }
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
        bGameIsEnding = true;
    }
}

int32 AGetThemGameMode::GetScore() const
{
    return FMath::FloorToInt32(TimeLeft);
}