// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

UCLASS()
class SHOOTERMCZOOTER_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Shoot();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpFrameRateIndependent(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightFrameRateIndependent(float AxisValue);

	UPROPERTY(EditAnywhere)
	float FOVRotationRate = 50.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;
	AGun* Gun;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Health = MaxHealth;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Die();
};
