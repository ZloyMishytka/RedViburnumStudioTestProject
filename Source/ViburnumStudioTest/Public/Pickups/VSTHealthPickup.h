// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/VSTBasePickup.h"
#include "VSTHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTHealthPickup : public AVSTBasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup, meta = (ClampMin = "1", ClampMax = "100"))
	float HealthAmount = 75.0f;

private:
	virtual bool GivePickupTo(APawn* Pawn) override;
};
