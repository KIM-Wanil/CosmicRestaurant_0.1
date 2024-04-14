// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureAppleItem.h"
#include "Item/AdventureItem/CRAdventureItemData.h"
#include "Components/BoxComponent.h"
ACRAdventureAppleItem::ACRAdventureAppleItem()
{
	Trigger->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	static ConstructorHelpers::FObjectFinder<UCRAdventureItemData> ItemDataRef(TEXT("/Game/CosmicRestaurant/Data/DA_CookingAppleItem.DA_CookingAppleItem"));
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
		Mesh->SetWorldScale3D(FVector(3, 3, 3));
		Trigger->SetRelativeLocation(FVector(0, 0, 5.0f));
		Mesh->SetMobility(EComponentMobility::Movable);
		Mesh->SetSimulatePhysics(true);
		//Mesh->SetEnableGravity(true);
	}
}

void ACRAdventureAppleItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//if (OtherActor->GetRootComponent()->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)

	//Mesh->SetMobility(EComponentMobility::Static);
	//Mesh->SetSimulatePhysics(false);
	//Mesh->SetEnableGravity(false);
}
