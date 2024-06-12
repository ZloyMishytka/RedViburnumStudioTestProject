// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/VSTHealthComponent.h"
#include "Components/VSTWeaponComponent.h"
#include "GameFramework/Character.h"
#include "VSTDroneCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UStaticMeshComponent;
class USceneComponent;
class UVSTHealthComponent;
class UVSTWeaponComponent;

UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTDroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVSTDroneCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UVSTWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	UVSTHealthComponent* GetHealthComponent() const { return HealthComponent; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UVSTHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UVSTWeaponComponent* WeaponComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HorizontalMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* VerticalMoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
	
private:
	bool bIsMovingForward = false;

	UFUNCTION()
	void DestroyDrone();
	
	void Move(const FInputActionValue& Value);
	void UpDown(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire();
};
