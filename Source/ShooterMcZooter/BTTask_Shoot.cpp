// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Shooter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (auto Controller = OwnerComp.GetAIOwner())
    {
        if (AShooter* AIShooter = Cast<AShooter>(Controller->GetPawn()))
        {
            AIShooter->Shoot();
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}
