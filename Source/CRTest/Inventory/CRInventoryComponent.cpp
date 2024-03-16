// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CRInventoryComponent.h"

// Sets default values for this component's properties
UCRInventoryComponent::UCRInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCRInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemMap.Add(EItemType::Stone, 0);
	ItemMap.Add(EItemType::Grass, 0);
	ItemMap.Add(EItemType::Wood, 0);
	ItemMap.Add(EItemType::Meat, 0);

	// ...
	
}


// Called every frame
void UCRInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCRInventoryComponent::GetItem(EItemType Type)
{
	if (ItemMap.Find(Type))
	{
		ItemMap[Type] += 1;
		UE_LOG(LogTemp, Log, TEXT("GatherItemTypeCount : %d"), ItemMap[Type]);
	}


}

