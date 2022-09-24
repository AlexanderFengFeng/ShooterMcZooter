// Fill out your copyright notice in the Description page of Project Settings.


#include "GetThemGameMode.h"

void AGetThemGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("This boi dead"));
}
