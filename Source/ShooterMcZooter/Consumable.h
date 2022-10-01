// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Consumable.generated.h"

UCLASS()
class SHOOTERMCZOOTER_API AConsumable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;
	float SpinRate = 180.f;

	virtual void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit);

};
