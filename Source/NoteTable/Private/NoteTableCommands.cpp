// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteTableCommands.h"

#define LOCTEXT_NAMESPACE "FNoteTableModule"

void FNoteTableCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NoteTable", "Bring up NoteTable window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
