// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VSTDroneCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AVSTDroneCharacter::AVSTDroneCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh());
	HealthComponent = CreateDefaultSubobject<UVSTHealthComponent>(TEXT("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UVSTWeaponComponent>(TEXT("WeaponComponent"));

	GetMesh()->ComponentTags.Add(FName("WeaponSlot"));
	CameraComponent->bUsePawnControlRotation = true;
	bIsMovingForward = false;
}

void AVSTDroneCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(CameraComponent);
	check(GetCharacterMovement());
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	HealthComponent->OnDeath.AddDynamic(this, &AVSTDroneCharacter::DestroyDrone);
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->ViewPitchMax = 20.0f;
}

void AVSTDroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(WeaponComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Moving
		EnhancedInputComponent->BindAction(HorizontalMoveAction, ETriggerEvent::Triggered, this, &AVSTDroneCharacter::Move);
		EnhancedInputComponent->BindAction(VerticalMoveAction, ETriggerEvent::Triggered, this, &AVSTDroneCharacter::UpDown);
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVSTDroneCharacter::Look);
		//WeaponActions
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AVSTDroneCharacter::Fire);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, WeaponComponent, &UVSTWeaponComponent::Reload);
	}
}

void AVSTDroneCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		bIsMovingForward = MovementVector.Y || MovementVector.X > 0.0f;
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AVSTDroneCharacter::UpDown(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();

	if (Controller != nullptr && AxisValue != 0)
	{
		AddMovementInput(GetActorUpVector(), AxisValue);
	}
}

void AVSTDroneCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	if(WeaponComponent->GetCurrentWeapon())
	{
		WeaponComponent->GetCurrentWeapon()->SetActorRelativeRotation(FRotator(CameraComponent->GetComponentRotation().Pitch, 0.0f, 0.0f));
	}
}

void AVSTDroneCharacter::DestroyDrone()
{
	GetCharacterMovement()->DisableMovement();
}

void AVSTDroneCharacter::Fire()
{
	if(GetHealthComponent()->IsDead()) return;
	GetWeaponComponent()->StartFire();
}
