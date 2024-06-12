// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "VSTAIController.generated.h"

/**
 * 
 */
UCLASS()
class VIBURNUMSTUDIOTEST_API AVSTAIController : public AAIController
{
	GENERATED_BODY()

public:
	AVSTAIController();

	void RotateControlledTurret(FRotator Rotation);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBehaviorTree* AIBehaviorTree;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEnemyDetected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Timer)
	float TimeRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Timer)
	float FirstDelayTimer = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Blackboard)
	FName KeyNameEnemy = TEXT("Enemy");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Blackboard)
	FName KeyNameIsEnemyDetected = TEXT("bIsEnemyDetected");
	
private:
	UPROPERTY()
	AActor* TargetEnemy;
	
	FTimerHandle TimerHandleSetValueInBlackboard;
	
	void SetEnemyInBlackboard();
	AActor* GetClosestEnemy();
};