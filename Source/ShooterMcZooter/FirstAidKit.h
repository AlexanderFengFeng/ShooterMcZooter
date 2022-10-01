// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Consumable.h"
#include "FirstAidKit.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API AFirstAidKit : public AConsumable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
