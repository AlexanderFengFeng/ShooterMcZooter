// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERMCZOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Visuals")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 10.f;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection, AController*& OwnerController);
};
