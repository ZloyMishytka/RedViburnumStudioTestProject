// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/VSTAmmoPickup.h"

#include "Player/VSTDroneCharacter.h"

bool AVSTAmmoPickup::GivePickupTo(APawn* Pawn)
{
	const AVSTDroneCharacter* DroneCharacter = Cast<AVSTDroneCharacter>(Pawn);
	if(!DroneCharacter) return false;

	if(!DroneCharacter->GetWeaponComponent() || !DroneCharacter->GetHealthComponent()) return false;

	return DroneCharacter->GetWeaponComponent()->TryAddAmmo(ClipsAmount);
}
