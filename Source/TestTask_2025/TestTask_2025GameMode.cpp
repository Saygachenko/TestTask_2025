// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTask_2025GameMode.h"
#include "TestTask_2025Character.h"
#include "UObject/ConstructorHelpers.h"

ATestTask_2025GameMode::ATestTask_2025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
