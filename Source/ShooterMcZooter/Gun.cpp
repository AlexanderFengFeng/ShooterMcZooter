// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	// Generate an FHitResult.
	FHitResult Hit;
	FVector ShotDirection;
	AController* OwnerController;

	if (GunTrace(Hit, ShotDirection, OwnerController))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, Hit.Location, ShotDirection.Rotation());
		if (AActor* Actor = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			Actor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			if (AShooter* Shooter = Cast<AShooter>(Actor))
			{
		        UGameplayStatics::PlaySoundAtLocation(this, MuzzleSound, Hit.Location, ShotDirection.Rotation());
				return;
			}
		}
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.Location, ShotDirection.Rotation());
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection, AController*& OwnerController)
{
	// Assign the owner and its controller to get the player view point.
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return false;
	OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return false;

	// Get the player viewpoint, projecting based on MaxRange.
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActors(TArray<AActor*> { this, GetOwner() });

    return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_GameTraceChannel1, Params);
}
