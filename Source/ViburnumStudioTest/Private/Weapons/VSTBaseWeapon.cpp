// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/VSTBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

AVSTBaseWeapon::AVSTBaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void AVSTBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = DefaultAmmo;
}

void AVSTBaseWeapon::StartFire()
{
	
}

void AVSTBaseWeapon::StopFire()
{
	
}

void AVSTBaseWeapon::MakeShot()
{

}

APlayerController* AVSTBaseWeapon::GetPlayerController() const
{
	const APawn* Player = Cast<APawn>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool AVSTBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if(!Pawn) return false;
	
	if(Pawn->IsPlayerControlled())
	{
		const APlayerController* Controller = GetPlayerController();
		if(!Controller) return false;
	
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleSocketWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
	return true;
}

bool AVSTBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AVSTBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

}

FVector AVSTBaseWeapon::GetMuzzleSocketWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void AVSTBaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;
	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StartReload();
	}
}

bool AVSTBaseWeapon::IsAmmoEmpty() const
{
	return  !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AVSTBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void AVSTBaseWeapon::StartReload()
{
	if(!CanReload() || !GetWorld()) return;
	
	bIsStartReload = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleStartReload, this, &AVSTBaseWeapon::ChangeClip, 0.1f, false, TimeReload);
}

bool AVSTBaseWeapon::TryAddAmmo(int32 ClipsAmount)
{
	if(CurrentAmmo.Infinite || CurrentAmmo.Clips == DefaultAmmo.Clips) return false;

	if(IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		StartReload();
	}
	else
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips);
	}
	return true;
}

void AVSTBaseWeapon::ChangeClip()
{
	bIsStartReload = false;
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if(!CurrentAmmo.Infinite)
	{
		CurrentAmmo.Clips--;
	}
}

bool AVSTBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0 && !bIsStartReload;
}
