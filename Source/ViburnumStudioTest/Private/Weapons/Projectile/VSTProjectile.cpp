// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectile/VSTProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AVSTProjectile::AVSTProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(8, 10);
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void AVSTProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileMovementComponent);
	check(CapsuleComponent);
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AVSTProjectile::OnProjectileHit);
	CapsuleComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SetLifeSpan(LifeTimeSpan);
}

void AVSTProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld()) return;

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 20, FColor::Red, false, 0.5f);
	ProjectileMovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, nullptr, {}, this, nullptr, bDoFullDamage);
	Destroy();
}

