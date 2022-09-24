// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    UBlackboardComponent* AIBlackboard = OwnerComp.GetBlackboardComponent();

    if (PlayerPawn == nullptr)
    {
        return;
    }
    if (auto Controller = OwnerComp.GetAIOwner())
    {
        if (Controller->LineOfSightTo(PlayerPawn))
        {
            AIBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        }
        else
        {
            AIBlackboard->ClearValue(GetSelectedBlackboardKey());
        }
    }
}