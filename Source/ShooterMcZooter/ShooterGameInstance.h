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
	void AddOrUpdateToHighScores(FString Key, int32 Value);
	int32 GetValueInHighScores(FString Key) const;
	bool HasHadPreviousHighScore(FString Key) const;
};
