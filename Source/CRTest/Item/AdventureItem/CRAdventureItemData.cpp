// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureItemData.h"

FPrimaryAssetId UCRAdventureItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("CRItemData", GetFName());
}
