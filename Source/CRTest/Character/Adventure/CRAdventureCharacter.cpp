// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Adventure/CRAdventureCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/AdventureItem/CRAdventureItemBase.h"
#include "Camera/CameraComponent.h"
#include "Interface/CRInteractingInterface.h"
#include "Kismet/KismetSystemLibrary.h"


ACRAdventureCharacter::ACRAdventureCharacter()
{
    /*static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Game/CosmicRestaurant/Input/IMC_Adventure.IMC_Adventure"));
    if (MappingContextRef.Object)
    {
        DefaultMappingContext = MappingContextRef.Object;

    }*/
	TracedItem = nullptr;
	//bCanGatherItem = false;
	CurrentState = EState::None;
	GatherItemType = EItemType::None;
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
void ACRAdventureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceItemToGet();
}
void ACRAdventureCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//ACRAdventureItemBase* Item = Cast<ACRAdventureItemBase>(OtherActor);
	//if (Item)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Item BeginOverlap"));

	//	bCanGatherItem = true;
	//	GatherItemType = Item->ItemData->Type;
	//	GatherItem = OtherActor;
	//	Item->SetRandomCustomDepth(true);
	//	//UE_LOG(LogTemp, Log, TEXT("name %s"), *UEnum::GetValueAsString(bCanGatherItem));
	//}
}

void ACRAdventureCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	//ACRAdventureItemBase* Item = Cast<ACRAdventureItemBase>(OtherActor);
	//if (Item)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Item EndOverlap"));

	//	bCanGatherItem = false;
	//	GatherItemType = EItemType::None;
	//	GatherItem = nullptr;
	//	Item->SetRandomCustomDepth(false);

	//	//UE_LOG(LogTemp, Log, TEXT("name %s"), *UEnum::GetValueAsString(bCanGatherItem));
	//}
}

void ACRAdventureCharacter::TraceItemToGet()
{
	FVector CameraLoc = FirstPersonCameraComponent->GetComponentLocation();
	FVector CameraForward = FirstPersonCameraComponent->GetForwardVector();
	FVector StartLoc = CameraLoc; // 레이저 시작 지점.
	FVector EndLoc = CameraLoc + (CameraForward * 500.0f); // 레이저 끝나는 지점.


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	//TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	ObjectTypes.Add(WorldStatic);
	//ObjectTypes.Add(WorldDynamic);

	TArray<AActor*> IgnoreActors; // 무시할 액터들.

	FHitResult HitResult; // 히트 결과 값 받을 변수.

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		StartLoc,
		EndLoc,
		ObjectTypes,
		false,
		IgnoreActors, // 무시할 것이 없다고해도 null을 넣을 수 없다.
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
		// 여기 밑에 3개는 기본 값으로 제공됨. 바꾸려면 적으면 됨.
		, FLinearColor::Red
		, FLinearColor::Green
		, 3.0f
	);
	if (Result == true)
	{
		ICRInteractingInterface* HitObject = Cast<ICRInteractingInterface>(HitResult.GetActor());
		TracedObject = HitObject;
		switch(HitObject->GetType())
		{
		case EObjectType::Tree:
			CurrentState = EState::CanShakeTree;
			break;
		case EObjectType::Item:

			TObjectPtr<ACRAdventureItemBase> HitItem = Cast<ACRAdventureItemBase>(HitObject);
			if (TracedItem != HitItem)
			{
				if (TracedItem != nullptr)
				{
					TracedItem->SetRandomCustomDepth(false);
				}
				TracedItem = HitItem;
				CurrentState = EState::CanGatherItem;
				//bCanGatherItem = true;
				GatherItemType = TracedItem->ItemData->Type;
				TracedItem->SetRandomCustomDepth(true);
			}
			break;
		}
	}
	else
	{
		if (TracedItem)
		{
			TracedItem->SetRandomCustomDepth(false);
			TracedItem = nullptr;
			//bCanGatherItem = false;
			CurrentState = EState::None;
			GatherItemType = EItemType::None;
		}
	}
	//if (Result == true )
	//{
	//	TObjectPtr<ACRAdventureItemBase> HitItem = Cast<ACRAdventureItemBase>(HitResult.GetActor());
	//	if (TracedItem != HitItem)
	//	{
	//		if (TracedItem != nullptr)
	//		{
	//			TracedItem->SetRandomCustomDepth(false);
	//		}
	//		TracedItem = HitItem;
	//		bCanGatherItem = true;
	//		GatherItemType = TracedItem->ItemData->Type;
	//		TracedItem->SetRandomCustomDepth(true);
	//	}
	//}
	//else
	//{
	//	if (TracedItem)
	//	{
	//		TracedItem->SetRandomCustomDepth(false);
	//		TracedItem = nullptr;	
	//		bCanGatherItem = false;
	//		GatherItemType = EItemType::None;
	//	}
	//}
}

void ACRAdventureCharacter::Interaction(const FInputActionValue& Value)
{
	Super::Interaction(Value);
	////UE_LOG(LogTemp, Log, TEXT("bCanGatherItem : %s"), *UEnum::GetValueAsString(bCanGatherItem));
	//UE_LOG(LogTemp, Log, TEXT("GatherItemType : %s"), *UEnum::GetValueAsString(GatherItemType));

	UE_LOG(LogTemp, Log, TEXT("State : %s"), *UEnum::GetValueAsString(CurrentState));

	switch (CurrentState)
	{
	case EState::CanGatherItem:
		UE_LOG(LogTemp, Log, TEXT("GetItem"));
		Inventory->GetItem(GatherItemType);
		if (TracedItem)
		{
			TracedItem->Destroy();
		}
		break;
	case EState::CanShakeTree:
		TracedObject->InteractCharacter();
		break;
	}
}
