// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterMcZooterGameModeBase.h"
#include "GetThemGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API AGetThemGameMode : public AShooterMcZooterGameModeBase
{
	GENERATED_BODY()

public:
	AGetThemGameMode();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndGame(bool bIsPlayerWinner) override;

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	virtual int32 GetScore() const override;

private:
	float TimeLeft = 30.f;
};
