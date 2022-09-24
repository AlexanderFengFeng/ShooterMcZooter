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
	virtual void PawnKilled(APawn* PawnKilled) override;

};
