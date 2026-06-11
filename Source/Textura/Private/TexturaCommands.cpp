// Copyright Epic Games, Inc. All Rights Reserved.

#include "TexturaCommands.h"

#define LOCTEXT_NAMESPACE "FTexturaModule"

void FTexturaCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Textura", "Bring up Textura window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
