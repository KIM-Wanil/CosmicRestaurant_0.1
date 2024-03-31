// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CRCharacterBase.h"
#include "Interface/CRCharacterItemInterface.h"
#include "Item/AdventureItem/CRAdventureItemBase.h"

#include "CRAdventureCharacter.generated.h"

/**
 * 
 */
UENUM()
enum EState {
	None = 0,
	CanGatherItem,
	CanShakeTree
};

UCLASS()
class CRTEST_API ACRAdventureCharacter : public ACRCharacterBase//, public ICRCharacterItemInterface
{
	GENERATED_BODY()
	

	ACRAdventureCharacter(); 
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void TraceItemToGet();

	virtual void Interaction(const FInputActionValue& Value) override;
	//virtual void TakeItem(UCRAdventureItemData* InItemData) override;

private:
	//bool bCanGatherItem;
	EItemType GatherItemType;
	TObjectPtr<ACRAdventureItemBase> TracedItem;
	ICRInteractingInterface* TracedObject;
	EState CurrentState = EState::None;
};
