// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/VSTHealthPickup.h"

#include "Player/VSTDroneCharacter.h"

bool AVSTHealthPickup::GivePickupTo(APawn* Pawn)
{
	const AVSTDroneCharacter* DroneCharacter = Cast<AVSTDroneCharacter>(Pawn);
	if(!DroneCharacter || !DroneCharacter->GetHealthComponent()) return false;

	return DroneCharacter->GetHealthComponent()->TryAddHealth(HealthAmount);
}
