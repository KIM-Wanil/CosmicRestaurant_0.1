// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CRCharacterBase.h"
#include "CRCookingCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRTEST_API ACRCookingCharacter : public ACRCharacterBase
{
	GENERATED_BODY()
	
public:
	ACRCookingCharacter();

protected:
	virtual void BeginPlay() override;
};
