// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CRInteractingInterface.h"
#include "CRAdventureItemBase.generated.h"

UCLASS()
class CRTEST_API ACRAdventureItemBase : public AActor, public ICRInteractingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRAdventureItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRandomCustomDepth(bool Input);

	virtual void InteractCharacter() override;
	virtual EObjectType GetType() override { return Type; };

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Item)
	TObjectPtr<class UCRAdventureItemData> ItemData;

	TObjectPtr<UMaterial> OutlineMaterial;
	enum EObjectType Type = EObjectType::Item;
};
