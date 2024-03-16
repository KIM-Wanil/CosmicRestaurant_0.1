// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CRCharacterBase.h"
#include "Interface/CRCharacterItemInterface.h"
#include "CRAdventureCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRTEST_API ACRAdventureCharacter : public ACRCharacterBase//, public ICRCharacterItemInterface
{
	GENERATED_BODY()
	

	ACRAdventureCharacter(); 
protected:
	virtual void BeginPlay() override;

private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void Interaction(const FInputActionValue& Value) override;
	//virtual void TakeItem(UCRAdventureItemData* InItemData) override;

private:
	bool bCanGatherItem;
	EItemType GatherItemType;
	TObjectPtr<AActor> GatherItem;
};
