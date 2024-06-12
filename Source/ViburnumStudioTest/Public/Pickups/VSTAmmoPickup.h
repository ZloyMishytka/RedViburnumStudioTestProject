// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/VSTBasePickup.h"
#include "VSTAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTAmmoPickup : public AVSTBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup, meta = (ClampMin = "1", ClampMax = "100"))
	int32 ClipsAmount = 5;

private:
	virtual bool GivePickupTo(APawn* Pawn) override;
};
