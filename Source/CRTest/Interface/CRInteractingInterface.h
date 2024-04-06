// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CRInteractingInterface.generated.h"

UENUM()
enum EObjectType {
	Portal=0,
	Tree,
	Item
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCRInteractingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRTEST_API ICRInteractingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InteractCharacter() = 0;
	virtual EObjectType GetType() = 0;
};
