// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Adventure/CRAdventureCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/AdventureItem/CRAdventureItemBase.h"


ACRAdventureCharacter::ACRAdventureCharacter()
{
    /*static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Game/CosmicRestaurant/Input/IMC_Adventure.IMC_Adventure"));
    if (MappingContextRef.Object)
    {
        DefaultMappingContext = MappingContextRef.Object;

    }*/
}

//void ACRAdventureCharacter::TakeItem(UCRAdventureItemData* InItemData)
//{
//	//UE_LOG(LogTemp, Log, TEXT("%d"), InItemData->Type);
//	Inventory->GetItem(InItemData->Type);
//}

void ACRAdventureCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACRAdventureCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACRAdventureItemBase* Item = Cast<ACRAdventureItemBase>(OtherActor);
	if (Item)
	{
		UE_LOG(LogTemp, Log, TEXT("Item BeginOverlap"));

		bCanGatherItem = true;
		GatherItemType = Item->ItemData->Type;
		GatherItem = OtherActor;
		//UE_LOG(LogTemp, Log, TEXT("name %s"), *UEnum::GetValueAsString(bCanGatherItem));
	}
}

void ACRAdventureCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	ACRAdventureItemBase* Item = Cast<ACRAdventureItemBase>(OtherActor);
	if (Item)
	{
		UE_LOG(LogTemp, Log, TEXT("Item EndOverlap"));

		bCanGatherItem = false;
		GatherItemType = EItemType::None;
		GatherItem = nullptr;
		//UE_LOG(LogTemp, Log, TEXT("name %s"), *UEnum::GetValueAsString(bCanGatherItem));
	}
}

void ACRAdventureCharacter::Interaction(const FInputActionValue& Value)
{
	Super::Interaction(Value);
	//UE_LOG(LogTemp, Log, TEXT("bCanGatherItem : %s"), *UEnum::GetValueAsString(bCanGatherItem));
	UE_LOG(LogTemp, Log, TEXT("GatherItemType : %s"), *UEnum::GetValueAsString(GatherItemType));

	if (bCanGatherItem)
	{
		UE_LOG(LogTemp, Log, TEXT("GetItem"));
		Inventory->GetItem(GatherItemType);
	}
	if (GatherItem)
	{
		GatherItem->Destroy();
	}
}
