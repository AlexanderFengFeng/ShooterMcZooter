// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        AIBlackboard = GetBlackboardComponent();
        AIBlackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
    AShooter* ControlledCharacter = Cast<AShooter>(GetPawn());
    if (ControlledCharacter)
    {
        return ControlledCharacter->IsDead();
    }
    return false;
}
