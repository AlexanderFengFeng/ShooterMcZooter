// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMcZooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERMCZOOTER_API AShooterMcZooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	bool bGameIsEnding = false;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndGame() { bGameIsEnding = true; }
	virtual void EndGame(bool bIsPlayerWinner) { bGameIsEnding = true; }

public:
	virtual void PawnKilled(APawn* PawnKilled);
	bool IsGameEnding() const { return bGameIsEnding; }
	UFUNCTION(BlueprintPure)
	virtual int32 GetScore() const { return 0; }
};
