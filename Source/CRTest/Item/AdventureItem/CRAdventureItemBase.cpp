// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AdventureItem/CRAdventureItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/CRCharacterItemInterface.h"
#include "Engine/AssetManager.h"


// Sets default values
ACRAdventureItemBase::ACRAdventureItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UMaterial> OutlineMaterialRef(TEXT("/Game/PCG_Test/M_OutLine.M_OutLine"));
	if (OutlineMaterialRef.Object)
	{
		OutlineMaterial = OutlineMaterialRef.Object;
	}

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetMaterial(1,OutlineMaterial);
	Trigger->SetCollisionProfileName(TEXT("CRTrigger"));
	Trigger->SetBoxExtent(FVector(40.0f, 45.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("Food"));
}

// Called when the game starts or when spawned
void ACRAdventureItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACRAdventureItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ACRAdventureItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRAdventureItemBase::SetRandomCustomDepth(bool Input)
{
	Mesh->SetRenderCustomDepth(Input);
}

