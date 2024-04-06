// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CRInteractingInterface.h"
#include "CRLevelTransferPortal.generated.h"

UCLASS()
class CRTEST_API ACRLevelTransferPortal : public AActor, public ICRInteractingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRLevelTransferPortal();

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	//TObjectPtr<class UStaticMeshComponent> PortalMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString GetTransferLevelName() { return TransferLevelName; }

	virtual void InteractCharacter() override;
	virtual EObjectType GetType() override { return Type; } ;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransferLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TransferVolume;
	enum EObjectType Type = EObjectType::Portal;
};
