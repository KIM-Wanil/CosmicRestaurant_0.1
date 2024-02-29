// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Adventure/CRAdventureCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACRAdventureCharacter::ACRAdventureCharacter()
{
    /*static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Game/CosmicRestaurant/Input/IMC_Adventure.IMC_Adventure"));
    if (MappingContextRef.Object)
    {
        DefaultMappingContext = MappingContextRef.Object;

    }*/
}

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
