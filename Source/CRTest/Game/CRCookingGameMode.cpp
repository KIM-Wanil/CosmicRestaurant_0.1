// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CRCookingGameMode.h"

ACRCookingGameMode::ACRCookingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_CRCookingCharacter.BP_CRCookingCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
