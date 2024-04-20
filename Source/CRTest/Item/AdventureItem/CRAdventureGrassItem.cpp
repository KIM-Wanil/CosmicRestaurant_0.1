// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureGrassItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"
#include "Components/BoxComponent.h"
ACRAdventureGrassItem::ACRAdventureGrassItem()
{
	Trigger->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	static ConstructorHelpers::FObjectFinder<UCRAdventureItemData> ItemDataRef(TEXT("/Game/CosmicRestaurant/Data/DA_AdventureGrassItem.DA_AdventureGrassItem"));
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
