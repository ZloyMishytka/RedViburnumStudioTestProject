// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/VSTProjectile.h"
#include "Weapons/VSTBaseWeapon.h"
#include "VSTLauncherWeapon.generated.h"

class AVSTProjectile;

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTLauncherWeapon : public AVSTBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:

	virtual void MakeShot() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<AVSTProjectile> ProjectileClass;
};
