// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"

bool UShooterGameInstance::TryToUpdateHighScore(int32 Score)
{
    if (IsScoreGreaterThanHighScore(Score))
    {
        HighScore = Score;
        return true;
    }
    return false;
}
