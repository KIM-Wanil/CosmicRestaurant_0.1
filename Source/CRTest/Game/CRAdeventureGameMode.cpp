// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CRAdeventureGameMode.h"

ACRAdeventureGameMode::ACRAdeventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_CRAdventureCharacter.BP_CRAdventureCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
