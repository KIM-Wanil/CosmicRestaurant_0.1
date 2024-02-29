// Copyright Epic Games, Inc. All Rights Reserved.

#include "CRTestGameMode.h"
#include "CRTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACRTestGameMode::ACRTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
