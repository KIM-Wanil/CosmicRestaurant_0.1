// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureGrassItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"

ACRAdventureGrassItem::ACRAdventureGrassItem()
{
	static ConstructorHelpers::FObjectFinder<UCRAdventureItemData> ItemDataRef(TEXT("/Game/CosmicRestaurant/Data/DA_AdventureGrassItem.DA_AdventureGrassItem"));
	if (ItemDataRef.Object)
	{
		ItemData = ItemDataRef.Object;
	}
	if (ItemData)
	{
		if (ItemData->ItemMesh.IsPending())
		{
			ItemData->ItemMesh.LoadSynchronous();
		}
		Mesh->SetStaticMesh(ItemData->ItemMesh.Get());
	}
}
