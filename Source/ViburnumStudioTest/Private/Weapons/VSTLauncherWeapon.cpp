// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/VSTLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"

void AVSTLauncherWeapon::StartFire()
{
	if(bIsStartReload || IsAmmoEmpty() || IsClipEmpty()) return;
	MakeShot();
}

void AVSTLauncherWeapon::MakeShot()
{
	if(!GetWorld()) return;
	
	FVector TraceStart = FVector::ZeroVector;
	FVector TraceEnd = FVector::ZeroVector;
	if(!GetTraceData(TraceStart, TraceEnd)) return;
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleSocketWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(WeaponMesh->GetSocketRotation(MuzzleSocketName), GetMuzzleSocketWorldLocation());
	AVSTProjectile* Projectile = GetWorld()->SpawnActorDeferred<AVSTProjectile>(ProjectileClass, SpawnTransform);
	if(Projectile)
	{
		Projectile->SetOwner(GetOwner());
		Projectile->SetShotDirection(Direction);
		Projectile->FinishSpawning(SpawnTransform);
	}
	DecreaseAmmo();
}
