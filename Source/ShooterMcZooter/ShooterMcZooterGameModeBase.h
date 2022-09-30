// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMcZooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API AShooterMcZooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	bool bGameIsEnding;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	virtual void PawnKilled(APawn* PawnKilled);
	bool IsGameEnding() const { return bGameIsEnding; }
};
