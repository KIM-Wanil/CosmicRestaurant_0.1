// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/AdventureItem/CRAdventureItemBase.h"
#include "CRAdventureAppleItem.generated.h"

/**
 * 
 */
UCLASS()
class CRTEST_API ACRAdventureAppleItem : public ACRAdventureItemBase
{
	GENERATED_BODY()
public:
	ACRAdventureAppleItem();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
