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
UENUM(BlueprintType)
enum class EState : uint8{
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

public:
	//bool bCanGatherItem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Type)
	EItemType GatherItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ItemID)
	FName ItemID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TracedItem)
	TObjectPtr<ACRAdventureItemBase> TracedItem;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TracedObject)
	ICRInteractingInterface* TracedObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = State)
	EState CurrentState = EState::None;
};
