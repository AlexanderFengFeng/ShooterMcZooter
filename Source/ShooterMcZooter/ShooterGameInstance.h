// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	TMap<FString, int32> HighScores;

public:
	bool AddOrUpdateHighScore(FString Key, int32 Score);
	UFUNCTION(BlueprintPure)
	int32 GetHighScore(FString Key) const;
	UFUNCTION(BlueprintPure)
	int32 IsScoreGreaterThanHighScore(FString Key, int32 Score) const;
	UFUNCTION(BlueprintPure)
	bool HasHadPreviousHighScore(FString Key) const;
};
