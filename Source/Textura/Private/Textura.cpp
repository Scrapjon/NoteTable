// Copyright Epic Games, Inc. All Rights Reserved.

#include "Textura.h"
#include "TexturaStyle.h"
#include "TexturaCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include  "UI/TexturaWindowWidget.h"

static const FName TexturaTabName("Textura");

#define LOCTEXT_NAMESPACE "FTexturaModule"

void FTexturaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTexturaStyle::Initialize();
	FTexturaStyle::ReloadTextures();

	FTexturaCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTexturaCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTexturaModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTexturaModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TexturaTabName, FOnSpawnTab::CreateRaw(this, &FTexturaModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTexturaTabTitle", "Textura"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTexturaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTexturaStyle::Shutdown();

	FTexturaCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TexturaTabName);
}

TSharedRef<SDockTab> FTexturaModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTexturaModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Textura.cpp"))
		);
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(STexturaWindowWidget)
		];
}

void FTexturaModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TexturaTabName);
}

void FTexturaModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTexturaCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTexturaCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTexturaModule, Textura)