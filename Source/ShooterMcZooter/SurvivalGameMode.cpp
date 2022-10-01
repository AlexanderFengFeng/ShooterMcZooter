// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"


void ASurvivalGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame();
        return;
    }
    Score++;
}

void ASurvivalGameMode::EndGame()
{
    Super::EndGame();
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), true);
    }
}
