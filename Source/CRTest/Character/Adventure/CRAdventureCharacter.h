// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CRCharacterBase.h"
#include "CRAdventureCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRTEST_API ACRAdventureCharacter : public ACRCharacterBase
{
	GENERATED_BODY()
	
public:
	ACRAdventureCharacter();
protected:
	virtual void BeginPlay() override;
};
