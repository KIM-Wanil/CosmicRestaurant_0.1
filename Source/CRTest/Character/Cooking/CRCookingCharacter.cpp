// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Cooking/CRCookingCharacter.h"
#include "EnhancedInputSubsystems.h"

ACRCookingCharacter::ACRCookingCharacter()
{
	//static ConstructorHelpers::F
	//static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Game/CosmicRestaurant/Input/IMC_Cooking.IMC_Cooking"));
	//if (MappingContextRef.Object)
	//{
	//	DefaultMappingContext = MappingContextRef.Object;

	//}
}

void ACRCookingCharacter::BeginPlay()
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
