// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "NoteTableStyle.h"

class FNoteTableCommands : public TCommands<FNoteTableCommands>
{
public:

	FNoteTableCommands()
		: TCommands<FNoteTableCommands>(TEXT("NoteTable"), NSLOCTEXT("Contexts", "NoteTable", "NoteTable Plugin"), NAME_None, FNoteTableStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};