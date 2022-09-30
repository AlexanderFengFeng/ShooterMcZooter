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
    TimeElapsed += DeltaSeconds;
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
            int32 TimeElapsedInInt = int32(TimeElapsed);
            if (GameInstance->HasHadPreviousHighScore(HighScoreKey))
            {
                TimeElapsedInInt = FMath::Max(TimeElapsedInInt, GameInstance->GetValueInHighScores(HighScoreKey));
            }
            GameInstance->AddOrUpdateToHighScores(HighScoreKey, TimeElapsedInInt);
        }
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
        bGameIsEnding = true;
    }
}
