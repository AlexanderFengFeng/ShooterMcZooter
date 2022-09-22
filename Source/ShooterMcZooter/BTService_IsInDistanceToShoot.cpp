// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsInDistanceToShoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_IsInDistanceToShoot::UBTService_IsInDistanceToShoot()
{
    NodeName = TEXT("Is In Distance To Shoot?");
}

void UBTService_IsInDistanceToShoot::TickNode(
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
        float Distance = FVector::Dist(PlayerPawn->GetActorLocation(),
                                       Controller->GetPawn()->GetActorLocation());
        UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *PlayerPawn->GetActorLocation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("AI: %s"), *Controller->GetPawn()->GetActorLocation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);
        AIBlackboard->SetValueAsBool(GetSelectedBlackboardKey(), Distance <= DistanceToShoot);

    }
}
