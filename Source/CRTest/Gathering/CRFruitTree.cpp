// Fill out your copyright notice in the Description page of Project Settings.


#include "Gathering/CRFruitTree.h"
#include "Components/BoxComponent.h"
// Sets default values
ACRFruitTree::ACRFruitTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree"));
	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = Tree;
	Volume->SetupAttachment(Tree);

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
		Fruits2.Add(TempFruit);
	}


}

void ACRFruitTree::BeGather()
{
	if (GatheringState == 0)
	{
		for (UStaticMeshComponent* Fruit : Fruits0)
		{
			Destroy(Fruit);
		}
	}

	else if (GatheringState == 1)
	{
		for (UStaticMeshComponent* Fruit : Fruits1)
		{
			Destroy(Fruit);
		}
	}

	else if (GatheringState == 2)
	{
		for (UStaticMeshComponent* Fruit : Fruits2)
		{
			Destroy(Fruit);
			bCanGathering = false;
		}
	}
}



