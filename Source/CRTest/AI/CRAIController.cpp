// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CRAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

ACRAIController::ACRAIController()
{
	//static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/CosmicRestaurant/Blueprints/Adventure/MonstersAI/BB_CRAdeventureMonster.BB_CRAdeventureMonster"));
	//if (BBAssetRef.Object)
	//{
	//	BBAsset = BBAssetRef.Object;
	//}

	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/CosmicRestaurant/Blueprints/Adventure/MonstersAI/BT_CRAdventureMonster.BT_CRAdventureMonster"));
	//if (BTAssetRef.Object)
	//{
	//	BTAsset = BTAssetRef.Object;
	//}
}

void ACRAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("SpawnPos"), GetPawn()->GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("RunAI"));
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void ACRAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponet = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponet)
	{
		BTComponet->StopTree();
	}
}

void ACRAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Log, TEXT("OnPossess"));

	RunAI();
}
