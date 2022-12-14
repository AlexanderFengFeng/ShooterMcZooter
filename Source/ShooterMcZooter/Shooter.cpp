// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterMcZooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	DefaultWalkSpeed = MovementComponent->MaxWalkSpeed;
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	Health = MaxHealth;
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStamina(DeltaTime);
}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpFrameRateIndependent"),
		                           this, &AShooter::LookUpFrameRateIndependent);
	PlayerInputComponent->BindAxis(TEXT("LookRightFrameRateIndependent"),
		                           this, &AShooter::LookRightFrameRateIndependent);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AShooter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AShooter::StopSprinting);
}

bool AShooter::IsDead() const
{
	return Health <= 0.f;
}

float AShooter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float AShooter::GetStaminaPercent() const
{
	return StaminaInSeconds / MaxStaminaInSeconds;
}

void AShooter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}


void AShooter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooter::LookUpFrameRateIndependent(float AxisValue)
{
	AddControllerPitchInput(AxisValue * FOVRotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}


void AShooter::LookRightFrameRateIndependent(float AxisValue)
{
	AddControllerYawInput(AxisValue * FOVRotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::Shoot()
{
    if (Gun)
    {
		Gun->PullTrigger();
    }
}

void AShooter::Sprint()
{
	if (MovementComponent && bCanSprint)
	{
		bIsSprinting = true;
	    MovementComponent->MaxWalkSpeed = DefaultWalkSpeed * SprintMultiplier;
	}
}

void AShooter::StopSprinting()
{
	if (MovementComponent)
	{
		bIsSprinting = false;
		MovementComponent->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

void AShooter::UpdateStamina(float DeltaTime)
{
    if (bIsSprinting)
    {
		StaminaInSeconds = FGenericPlatformMath::Max(0, StaminaInSeconds - DeltaTime);
		if (StaminaInSeconds == 0)
		{
			bCanSprint = false;
			StopSprinting();
		}
    }
    else if (!bIsSprinting)
    {
		if (StaminaInSeconds >= StaminaCanSprintInSeconds)
		{
			bCanSprint = true;
		}
		StaminaInSeconds = FGenericPlatformMath::Min(MaxStaminaInSeconds, StaminaInSeconds + DeltaTime);
    }
}

float AShooter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent, 
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(
		DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	if (IsDead())
	{
		Die();
	}
	return DamageToApply;
}

void AShooter::Die()
{
	SetActorEnableCollision(false);
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	AShooterMcZooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterMcZooterGameModeBase>();
	GameMode->PawnKilled(this);
	DetachFromControllerPendingDestroy();
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&AShooter::DestroyDelegate,
		DestroyDelay);
}

void AShooter::DestroyDelegate()
{
	if (Gun)
	{
	    Gun->Destroy();
	}
	Destroy();
}
