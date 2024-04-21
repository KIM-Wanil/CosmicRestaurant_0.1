// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CRCharacterAIInterface.h"
#include "CRAdeventureMonster.generated.h"

UCLASS()
class CRTEST_API ACRAdeventureMonster : public ACharacter, public ICRCharacterAIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACRAdeventureMonster();
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAITurnSpeed() override;
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
