// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "TexturaStyle.h"

class FTexturaCommands : public TCommands<FTexturaCommands>
{
public:

	FTexturaCommands()
		: TCommands<FTexturaCommands>(TEXT("Textura"), NSLOCTEXT("Contexts", "Textura", "Textura Plugin"), NAME_None, FTexturaStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};