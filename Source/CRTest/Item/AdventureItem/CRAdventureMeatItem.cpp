// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureMeatItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"

ACRAdventureMeatItem::ACRAdventureMeatItem()
{
	static ConstructorHelpers::FObjectFinder<UCRAdventureItemData> ItemDataRef(TEXT("/Game/CosmicRestaurant/Data/DA_MeatItem.DA_MeatItem"));
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
