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
	int32 HighScore = 0;

public:
	UFUNCTION(BlueprintCallable)
	bool TryToUpdateHighScore(int32 Score);
	UFUNCTION(BlueprintCallable)
	void ResetHighScore() { HighScore = 0; }
	UFUNCTION(BlueprintPure)
	int32 GetHighScore() const { return HighScore; }
	UFUNCTION(BlueprintPure)
	bool IsScoreGreaterThanHighScore(int32 Score) const { return Score > HighScore; };
};
