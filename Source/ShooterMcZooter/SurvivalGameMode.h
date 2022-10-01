// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterMcZooterGameModeBase.h"
#include "SurvivalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API ASurvivalGameMode : public AShooterMcZooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	virtual int32 GetScore() const override { return Score; }

protected:
	virtual void EndGame() override;

private:
	int32 Score = 0;
};
