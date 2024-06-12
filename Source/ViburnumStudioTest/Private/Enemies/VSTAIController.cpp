// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/VSTAIController.h"
#include "Enemies/VSTTurretPawn.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/VSTDroneCharacter.h"

AVSTAIController::AVSTAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 10000.0f;
	SightConfig->LoseSightRadius = 12000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AVSTAIController::BeginPlay()
{
	Super::BeginPlay();

	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSetValueInBlackboard, this, &AVSTAIController::SetEnemyInBlackboard, TimeRate, true, FirstDelayTimer);
}

void AVSTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(!AIBehaviorTree) return;
	RunBehaviorTree(AIBehaviorTree);
}

void AVSTAIController::SetEnemyInBlackboard()
{
	AActor* Enemy = GetClosestEnemy();
	if(Enemy)
	{
		GetBlackboardComponent()->SetValueAsObject(KeyNameEnemy, Enemy);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(KeyNameEnemy);
	}
	GetBlackboardComponent()->SetValueAsBool(KeyNameIsEnemyDetected, bIsEnemyDetected);
}

AActor* AVSTAIController::GetClosestEnemy()
{
	TArray<AActor*> DetectedActors;

	AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), DetectedActors);
	if(DetectedActors.IsEmpty())
	{
		bIsEnemyDetected = false;
		return nullptr;
	}
	
	for (AActor* DetectedActor : DetectedActors)
	{
		if(DetectedActor->IsA(AVSTDroneCharacter::StaticClass()))
		{
			const AVSTDroneCharacter* DroneCharacter = Cast<AVSTDroneCharacter>(DetectedActor);
			if(DroneCharacter->GetHealthComponent()->IsDead()) return nullptr;
			bIsEnemyDetected = true;
			return DetectedActor;
		}
	}
	bIsEnemyDetected = false;
	return nullptr;
}

void AVSTAIController::RotateControlledTurret(FRotator Rotation)
{
	AVSTTurretPawn* TurretPawn = Cast<AVSTTurretPawn>(GetInstigator());
	if(!TurretPawn) return;

	AActor* Enemy = nullptr;
	if(bIsEnemyDetected)
	{
		Enemy = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(KeyNameEnemy));
	}
	TurretPawn->RotateTurret(Rotation, Enemy);
}