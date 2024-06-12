// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/VSTBasePickup.h"

AVSTBasePickup::AVSTBasePickup()
{
 	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->InitSphereRadius(60);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

}

void AVSTBasePickup::BeginPlay()
{
	Super::BeginPlay();
}

void AVSTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn* Pawn = Cast<APawn>(OtherActor);
	if(GivePickupTo(Pawn))
	{
		Destroy();
	}
}

bool AVSTBasePickup::GivePickupTo(APawn* Pawn)
{
	return false;
}

