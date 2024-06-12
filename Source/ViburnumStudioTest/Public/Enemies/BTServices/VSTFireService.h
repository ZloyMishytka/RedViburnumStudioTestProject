// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "VSTFireService.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API UVSTFireService : public UBTService
{
	GENERATED_BODY()

public:
	UVSTFireService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector BlackboardKey;
};
