// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSTProjectile.generated.h"

class USceneComponent;
class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AVSTProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float LifeTimeSpan = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float DamageAmount = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float DamageRadius = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	bool bDoFullDamage = false;
	
private:
	FVector ShotDirection = FVector::ZeroVector;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
