// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureStoneItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"

ACRAdventureStoneItem::ACRAdventureStoneItem()
{
	static ConstructorHelpers::FObjectFinder<UCRAdventureItemData> ItemDataRef(TEXT("/Game/CosmicRestaurant/Data/DA_AdventureStoneItem.DA_AdventureStoneItem"));
	if (ItemDataRef.Object)
	{
		ItemData = ItemDataRef.Object;
	}
	if (ItemData)
	{
		if (ItemData->AdventureItemMesh.IsPending())
		{
			ItemData->AdventureItemMesh.LoadSynchronous();
		}
		Mesh->SetStaticMesh(ItemData->AdventureItemMesh.Get());
	}
	
}
