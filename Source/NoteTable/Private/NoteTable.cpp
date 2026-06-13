// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteTable.h"
#include "NoteTableStyle.h"
#include "NoteTableCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "UI/NWindowWidget.h"

static const FName NoteTableTabName("NoteTable");

#define LOCTEXT_NAMESPACE "FNoteTableModule"

void FNoteTableModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNoteTableStyle::Initialize();
	FNoteTableStyle::ReloadTextures();

	FNoteTableCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNoteTableCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNoteTableModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNoteTableModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NoteTableTabName, FOnSpawnTab::CreateRaw(this, &FNoteTableModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNoteTableTabTitle", "NoteTable"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNoteTableModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNoteTableStyle::Shutdown();

	FNoteTableCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NoteTableTabName);
}

TSharedRef<SDockTab> FNoteTableModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNoteTableModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NoteTable.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNWindowWidget)
		];
}

void FNoteTableModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(NoteTableTabName);
}

void FNoteTableModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNoteTableCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNoteTableCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNoteTableModule, NoteTable)