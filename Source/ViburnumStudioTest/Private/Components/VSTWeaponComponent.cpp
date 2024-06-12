// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VSTWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

UVSTWeaponComponent::UVSTWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FAmmoData UVSTWeaponComponent::GetAmmoData() const
{
	if(!CurrentWeapon) return FAmmoData {0, 0, false};

	return CurrentWeapon->GetAmmoData();
}

void UVSTWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UVSTWeaponComponent::SpawnWeapon()
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!PawnOwner || !GetWorld()) return;

	AVSTBaseWeapon* Weapon = GetWorld()->SpawnActor<AVSTBaseWeapon>(WeaponClass);
	if(!Weapon) return;
	
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	TArray<UActorComponent*> ActorComponents = PawnOwner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), NameWeaponTag);
	USkeletalMeshComponent* SkeletalMesh = nullptr;
	for (UActorComponent* ActorComponent : ActorComponents)
	{
		if(ActorComponent->IsA(USceneComponent::StaticClass()) && ActorComponent->ComponentTags.Contains(NameWeaponTag))
		{
			SkeletalMesh = Cast<USkeletalMeshComponent>(ActorComponent);
		}
	}
	if(!SkeletalMesh) return;
	Weapon->AttachToComponent(SkeletalMesh, AttachmentTransformRules, NameWeaponSocket);
	Weapon->SetOwner(PawnOwner);
	CurrentWeapon = Weapon;
}

void UVSTWeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void UVSTWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UVSTWeaponComponent::Reload()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StartReload();
}

bool UVSTWeaponComponent::TryAddAmmo(int32 ClipsAmount)
{
	if(!CurrentWeapon) return false;

	return CurrentWeapon->TryAddAmmo(ClipsAmount);
}
