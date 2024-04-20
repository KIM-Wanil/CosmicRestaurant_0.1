// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureStoneItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"
#include "Components/BoxComponent.h"

ACRAdventureStoneItem::ACRAdventureStoneItem()
{
	Trigger->SetBoxExtent(FVector(40.0f, 45.0f, 30.0f));
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
