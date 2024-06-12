// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VSTHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIBURNUMSTUDIOTEST_API UVSTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVSTHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return Health; }
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.0f; }
	
	float GetHealth() const { return  Health; }
	bool IsHealthFull() const { return Health >= MaxHealth; }
	bool TryAddHealth(float HealthAmount);

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	
	FOnHealthChanged OnHealthChanged;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (ClampMin = "1.0", ClampMax = "1000"))
	float MaxHealth = 100.0f;

private:
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void SetHealth(float NewHealth);
	
	float Health = 0.0f;
	
};
