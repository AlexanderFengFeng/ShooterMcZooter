// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsInDistanceToShoot.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMCZOOTER_API UBTService_IsInDistanceToShoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_IsInDistanceToShoot();

protected:

	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	float DistanceToShoot = 500.f;
	
};