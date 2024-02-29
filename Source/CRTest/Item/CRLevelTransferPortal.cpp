// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CRLevelTransferPortal.h"
#include "Character/CRCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACRLevelTransferPortal::ACRLevelTransferPortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	/*PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	RootComponent = PortalMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PortalMeshRef(TEXT(""));
	if (PortalMeshRef.Object)
	{
		PortalMesh->SetStaticMesh(PortalMeshRef.Object);
	}*/
}

// Called when the game starts or when spawned
void ACRLevelTransferPortal::BeginPlay()
{
	Super::BeginPlay();

}

//void ACRLevelTransferPortal::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	ACRCharacterBase* Character = Cast<ACRCharacterBase>(OtherActor);
//	if (Character)
//	{
//		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
//		
//	}
//}
//
//void ACRLevelTransferPortal::NotifyActorEndOverlap(AActor* OtherActor)
//{
//}

// Called every frame
void ACRLevelTransferPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

