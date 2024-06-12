// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/VSTTurretPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include <cmath>
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/VSTWeaponComponent.h"
#include "Components/VSTHealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

AVSTTurretPawn::AVSTTurretPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	TurretSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretSkeletalMeshComponent"));
	TurretSkeletalMeshComponent->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UVSTHealthComponent>(TEXT("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UVSTWeaponComponent>(TEXT("WeaponComponent"));

	TurretSkeletalMeshComponent->ComponentTags.Add(FName("WeaponSlot"));
}

void AVSTTurretPawn::RotateTurret(const FRotator Rotation, const AActor* Enemy)
{
	if(!GetWorld()) return;
	if(Enemy)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleSmoothRotateTurret);
		const FVector LocationEnemy = Enemy->GetActorLocation();
		const FVector LocationAIPawn = GetActorLocation();
		FVector Direction = LocationEnemy - LocationAIPawn;
		Direction.Z = 0;
		FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(NewRotation);

		if(!WeaponComponent || !WeaponComponent->GetCurrentWeapon()) return;
		const FRotator WeaponRotate = UKismetMathLibrary::FindLookAtRotation(LocationAIPawn, LocationEnemy);
		WeaponComponent->GetCurrentWeapon()->SetActorRelativeRotation(FRotator(WeaponRotate.Pitch, 0.0f, 0.0f));
	}
	else
	{
		TimerDelegateSmoothRotateTurret.BindUObject(this, &AVSTTurretPawn::SmoothRotateTurret, Rotation);
		GetWorld()->GetTimerManager().SetTimer(TimerHandleSmoothRotateTurret, TimerDelegateSmoothRotateTurret, DeltaTimeRotation, true);
		if(!WeaponComponent || !WeaponComponent->GetCurrentWeapon()) return;
		WeaponComponent->GetCurrentWeapon()->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
}

void AVSTTurretPawn::SmoothRotateTurret(const FRotator Rotation)
{
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), Rotation, DeltaTimeRotation, InterpolateSpeedRotation);
	SetActorRotation(NewRotation);
	if(std::floor(Rotation.Yaw) == std::floor(GetActorRotation().Yaw))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleSmoothRotateTurret);
	}
}

void AVSTTurretPawn::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	HealthComponent->OnDeath.AddDynamic(this, &AVSTTurretPawn::DestroyTurret);
}

void AVSTTurretPawn::DestroyTurret()
{
	AAIController* AIController = Cast<AAIController>(Controller);
	if(AIController)
	{
		AIController->BrainComponent->Cleanup();
	}
	WeaponComponent->GetCurrentWeapon()->Destroy();
	Destroy();
}