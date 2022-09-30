// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"

void UShooterGameInstance::AddOrUpdateToHighScores(FString Key, int32 Value)
{
    HighScores.Emplace(Key, Value);
}

int32 UShooterGameInstance::GetValueInHighScores(FString Key) const
{
    return HighScores[Key];
}

bool UShooterGameInstance::HasHadPreviousHighScore(FString Key) const
{
    return HighScores.Contains(Key);
}
