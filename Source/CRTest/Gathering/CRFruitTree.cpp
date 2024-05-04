// Fill out your copyright notice in the Description page of Project Settings.


#include "Gathering/CRFruitTree.h"
#include "Components/BoxComponent.h"
#include "Item/AdventureItem/CRAdventureAppleItem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACRFruitTree::ACRFruitTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree"));
	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = Tree;
	Volume->SetupAttachment(Tree);
	Volume->SetCollisionProfileName(TEXT("Food"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshRef(TEXT("/Game/UsedAssets/Tree/SM_FruitTree.SM_FruitTree"));
	if (TreeMeshRef.Object)
	{
		Tree -> SetStaticMesh(TreeMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FruitMeshRef(TEXT("/Game/UsedAssets/Food_Pack_01/Meshes/Food_Fruit_Apple_01.Food_Fruit_Apple_01"));

	for (int i = 0; i < 3; i++)
	{
		TObjectPtr<UStaticMeshComponent> TempFruit;

		FString FruitName = TEXT("Fruit0") + FString::FromInt(i);

		TempFruit = CreateDefaultSubobject<UStaticMeshComponent>( FName(*FruitName));
		if (FruitMeshRef.Object)
		{
			TempFruit->SetStaticMesh(FruitMeshRef.Object);
		}
		TempFruit->SetupAttachment(Tree);
		Fruits0.Add(TempFruit);
	}
	for (int i = 0; i < 3; i++)
	{
		TObjectPtr<UStaticMeshComponent> TempFruit;

		FString FruitName = TEXT("Fruit1") + FString::FromInt(i);

		TempFruit = CreateDefaultSubobject<UStaticMeshComponent>(FName(*FruitName));
		if (FruitMeshRef.Object)
		{
			TempFruit->SetStaticMesh(FruitMeshRef.Object);
		}
		TempFruit->SetupAttachment(Tree);
		Fruits1.Add(TempFruit);
	}
	for (int i = 0; i < 3; i++)
	{
		TObjectPtr<UStaticMeshComponent> TempFruit;

		FString FruitName = TEXT("Fruit2") + FString::FromInt(i);

		TempFruit = CreateDefaultSubobject<UStaticMeshComponent>(FName(*FruitName));
		if (FruitMeshRef.Object)
		{
			TempFruit->SetStaticMesh(FruitMeshRef.Object);
		}
		TempFruit->SetupAttachment(Tree);
		Fruits2.Add(TempFruit);
	}


}

void ACRFruitTree::InteractCharacter()
{
	BeGather();
}

void ACRFruitTree::BeGather()
{
	if (bCanGathering == false) return;

	if (GatheringState == 0)
	{
		for (UStaticMeshComponent* Obj : Fruits0)
		{
			Obj->DestroyComponent();
		}
		SpawnFruit(TEXT("SpawnLoc1"));
	}

	else if (GatheringState == 1)
	{
		for (UStaticMeshComponent* Obj : Fruits1)
		{
			Obj->DestroyComponent();
		}
		SpawnFruit(TEXT("SpawnLoc2"));
	}
	else if (GatheringState == 2)
	{
		for (UStaticMeshComponent* Obj : Fruits2)
		{
			Obj->DestroyComponent();
			bCanGathering = false;
		}	
		SpawnFruit(TEXT("SpawnLoc3"));
	}
	GatheringState++;


}

void ACRFruitTree::SpawnFruit(FName SocketName)
{
	//FString BPClassPath = TEXT("/Script/CRTest.CRAdventureAppleItem");
	//UClass* BPClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BPClassPath);


	FVector SpawnLocation = Tree->GetSocketLocation(SocketName); // 원하는 위치로 수정하세요.
	//ACRAdventureAppleItem* NewActor = GetWorld()->SpawnActor<ACRAdventureAppleItem>(ACRAdventureAppleItem::StaticClass(), SpawnLocation, FRotator::ZeroRotator);


	//UObject* cls = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/CosmicRestaurant/Blueprints/Item/BP_CRAdventureFruitItem.BP_CRAdventureFruitItem"));
	//UBlueprint* bp = Cast<UBlueprint>(cls);
	//TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;
	//GetWorld()->SpawnActor<AActor>(blockBP, SpawnLocation, FRotator::ZeroRotator);



	TSubclassOf<AActor> BlueprintFruitItem = LoadClass<AActor>(nullptr, TEXT("/Game/CosmicRestaurant/Blueprints/Item/BP_CRAdventureFruitItem.BP_CRAdventureFruitItem_C"));
	if (BlueprintFruitItem)
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BlueprintFruitItem, SpawnLocation, FRotator::ZeroRotator);
	}

}



