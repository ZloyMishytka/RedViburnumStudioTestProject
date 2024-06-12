// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VSTHealthComponent.h"
#include "GameFramework/Actor.h"

UVSTHealthComponent::UVSTHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVSTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	if(AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UVSTHealthComponent::OnTakeAnyDamageHandle);
	}
}

void UVSTHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || IsDead()) return;

	SetHealth(Health - Damage);
	if(IsDead()) OnDeath.Broadcast();
}

void UVSTHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}

bool UVSTHealthComponent::TryAddHealth(float HealthAmount)
{
	if(IsDead() || IsHealthFull()) return false;
	
	SetHealth(Health + HealthAmount);
	return true;
}
