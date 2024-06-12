// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/VSTBaseWeapon.h"
#include "VSTWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIBURNUMSTUDIOTEST_API UVSTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVSTWeaponComponent();

	UFUNCTION(BlueprintCallable)
	FAmmoData GetAmmoData() const;
	
	void StartFire();
	void StopFire();
	void Reload();
	bool TryAddAmmo(int32 ClipsAmount);
	AVSTBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<AVSTBaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FName NameWeaponTag = TEXT("WeaponSlot");

	UPROPERTY(EditAnywhere, Category = Weapon)
	FName NameWeaponSocket = TEXT("WeaponSocket");
private:
	UPROPERTY()
	AVSTBaseWeapon* CurrentWeapon;
	
	void SpawnWeapon();
};
