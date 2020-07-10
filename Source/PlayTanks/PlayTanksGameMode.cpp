// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayTanksGameMode.h"
#include "PlayTanksPawn.h"

APlayTanksGameMode::APlayTanksGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = APlayTanksPawn::StaticClass();
}

