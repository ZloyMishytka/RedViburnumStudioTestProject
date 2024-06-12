// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "VSTBasePickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	AVSTBasePickup();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, Category = Pickup)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = Pickup)
	UStaticMeshComponent* StaticMeshComponent;

private:
	virtual bool GivePickupTo(APawn* Pawn);
};
