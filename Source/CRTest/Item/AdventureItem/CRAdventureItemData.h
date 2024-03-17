// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CRAdventureItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None = 0,
	Stone ,
	Wood,
	Meat,
	Grass
};

UCLASS()
class CRTEST_API UCRAdventureItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TSoftObjectPtr<UStaticMesh> ItemMesh;
};
