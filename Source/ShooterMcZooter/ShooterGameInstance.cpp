// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"

bool UShooterGameInstance::AddOrUpdateHighScore(FString Key, int32 Score)
{
    if (!HasHadPreviousHighScore(Key) || IsScoreGreaterThanHighScore(Key, Score))
    {
        HighScores.Emplace(Key, Score);
        return true;
    }
    return false;
}

int32 UShooterGameInstance::IsScoreGreaterThanHighScore(FString Key, int32 Score) const
{
    return Score > GetHighScore(Key);
}

int32 UShooterGameInstance::GetHighScore(FString Key) const
{
    return HighScores[Key];
}

bool UShooterGameInstance::HasHadPreviousHighScore(FString Key) const
{
    return HighScores.Contains(Key);
}