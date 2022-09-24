// Fill out your copyright notice in the Description page of Project Settings.


#include "GetThemGameMode.h"

void AGetThemGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled);
    if (PlayerController)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}
