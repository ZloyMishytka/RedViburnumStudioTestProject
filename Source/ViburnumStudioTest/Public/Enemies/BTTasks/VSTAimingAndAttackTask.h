// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "VSTAimingAndAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API UVSTAimingAndAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UVSTAimingAndAttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
