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

public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
