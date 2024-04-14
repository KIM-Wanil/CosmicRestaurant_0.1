// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CRInteractingInterface.h"
#include "CRFruitTree.generated.h"

UCLASS()
class CRTEST_API ACRFruitTree : public AActor, public ICRInteractingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRFruitTree();
	virtual void InteractCharacter() override;
	virtual EObjectType GetType() override { return Type; };
	void BeGather();
	void SpawnApple();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Fruit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UStaticMeshComponent*> Fruits0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UStaticMeshComponent*> Fruits1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UStaticMeshComponent*> Fruits2;

	int8 GatheringState = 0;
	int8 bCanGathering = true;
	enum EObjectType Type = EObjectType::Tree;
};
