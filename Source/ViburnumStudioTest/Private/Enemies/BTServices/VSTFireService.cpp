// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BTServices/VSTFireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/VSTWeaponComponent.h"
#include "Enemies/VSTTurretPawn.h"

UVSTFireService::UVSTFireService()
{
	NodeName = TEXT("Fire");
}

void UVSTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
    const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if(!Controller || !Blackboard) return;
    
    AVSTTurretPawn* Pawn = Cast<AVSTTurretPawn>(Controller->GetPawn());
    if(!Pawn) return;
	AActor* Enemy = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if(Enemy)
	{
		Pawn->GetWeaponComponent()->StartFire();
	}
	else
	{
		Pawn->GetWeaponComponent()->StopFire();
	}
}
