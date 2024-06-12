// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BTTasks/VSTAimingAndAttackTask.h"

#include "Enemies/VSTAIController.h"

UVSTAimingAndAttackTask::UVSTAimingAndAttackTask()
{
	NodeName = TEXT("Aiming");
}

EBTNodeResult::Type UVSTAimingAndAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	AVSTAIController* VSTController = Cast<AVSTAIController>(Controller);
	if(!VSTController) return EBTNodeResult::Failed;
	
	VSTController->RotateControlledTurret(FRotator::ZeroRotator);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
