// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

private:

	UBTTask_Shoot();

protected:

    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
