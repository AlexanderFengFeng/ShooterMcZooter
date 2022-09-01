// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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