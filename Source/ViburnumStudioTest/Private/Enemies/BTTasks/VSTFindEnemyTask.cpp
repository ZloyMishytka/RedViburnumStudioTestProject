// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BTTasks/VSTFindEnemyTask.h"

#include "Enemies/VSTAIController.h"
#include "Enemies/VSTTurretPawn.h"

UVSTFindEnemyTask::UVSTFindEnemyTask()
{
	NodeName = TEXT("FindEnemy");
}

EBTNodeResult::Type UVSTFindEnemyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	AVSTAIController* VSTController = Cast<AVSTAIController>(Controller);
	if(!VSTController) return EBTNodeResult::Failed;
	
	const float RandomYaw = FMath::FRandRange(0.0f, 360.0f);
	const FRotator RandomRotationByYaw = FRotator(0.0f, RandomYaw, 0.0f);
	VSTController->RotateControlledTurret(RandomRotationByYaw);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
