// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Adventure/CRAdeventureMonster.h"
#include "AI/CRAIController.h"

// Sets default values
ACRAdeventureMonster::ACRAdeventureMonster()
{
	AIControllerClass = ACRAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

float ACRAdeventureMonster::GetAIPatrolRadius()
{
	return 1000.0f;
}

float ACRAdeventureMonster::GetAIDetectRange()
{
	return 2000.0f;
}

float ACRAdeventureMonster::GetAITurnSpeed()
{
	return 100.0f;
}

//// Called when the game starts or when spawned
//void ACRAdeventureMonster::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ACRAdeventureMonster::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void ACRAdeventureMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

