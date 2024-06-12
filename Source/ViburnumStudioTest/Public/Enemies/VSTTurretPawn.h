// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "VSTTurretPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UVSTHealthComponent;
class UVSTWeaponComponent;

UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTTurretPawn : public APawn
{
	GENERATED_BODY()

public:
	AVSTTurretPawn();

	void RotateTurret(const FRotator NewRotation, const AActor* Enemy);
	UVSTWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* TurretSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UVSTHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UVSTWeaponComponent* WeaponComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	FName WeaponSocketName = TEXT("WeaponSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Turret)
	float DeltaTimeRotation = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Turret)
	float InterpolateSpeedRotation = 1.0f;
	
private:
	FTimerHandle TimerHandleSmoothRotateTurret;
	FTimerDelegate TimerDelegateSmoothRotateTurret;

	void SmoothRotateTurret(const FRotator Rotation);

	UFUNCTION()
	void DestroyTurret();
};