// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "VSTFindEnemyTask.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API UVSTFindEnemyTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UVSTFindEnemyTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
