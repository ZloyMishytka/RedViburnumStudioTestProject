// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSTBaseWeapon.generated.h"


class USceneComponent;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	int32 Bullets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!Infinite"))
	int32 Clips = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	bool Infinite = false;
};

UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AVSTBaseWeapon();
	
	virtual void StartFire();
	virtual void StopFire();
	void StartReload();
	bool TryAddAmmo(int32 ClipsAmount);
	FAmmoData GetAmmoData() const { return CurrentAmmo; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	FName MuzzleSocketName = TEXT("Muzzle");;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	float TraceMaxDistance = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	FAmmoData DefaultAmmo{3, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	float TimeReload = 4.0f;
	
	virtual void BeginPlay() override;
	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void DecreaseAmmo();
	void ChangeClip();
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool CanReload() const;
	FVector GetMuzzleSocketWorldLocation() const;
	APlayerController* GetPlayerController() const;

	bool bIsStartReload = false;
	
private:
	FAmmoData CurrentAmmo{0, 0, false};
	FTimerHandle TimerHandleStartReload;
};
