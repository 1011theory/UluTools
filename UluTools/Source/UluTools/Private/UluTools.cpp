// Copyright Epic Games, Inc. All Rights Reserved.

#include "UluTools.h"

#include "LevelEditor.h"
#include "Selection.h"
#include "ULUIcons.h"
#include "EditorExtensions/ULUCommands.h"

#define LOCTEXT_NAMESPACE "FUluToolsModule"

void FUluToolsModule::StartupModule()
{
	FUluIconsStyle::Initialize();

	BindMenuCommands();
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	auto& MenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();

	MenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FUluToolsModule::GetLevelViewportContextMenuExtender));
	LevelViewportExtenderHandle = MenuExtenders.Last().GetHandle(); //this is to reference it later when we want to remove the extender.
}


void FUluToolsModule::ShutdownModule()
{
	if (LevelViewportExtenderHandle.IsValid()) //Remove the level viewport Menu extender
	{
		FLevelEditorModule* LevelEditorModule = FModuleManager::Get().GetModulePtr<FLevelEditorModule>("LevelEditor");
		if (LevelEditorModule)
		{
			typedef FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors DelegateType;
			LevelEditorModule->GetAllLevelViewportContextMenuExtenders().RemoveAll(
				[this](const DelegateType& In) { return In.GetHandle() == LevelViewportExtenderHandle; });
		}
	}
	FUluIconsStyle::Shutdown();
}


TSharedRef<FExtender> FUluToolsModule::GetLevelViewportContextMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> InActors)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	TArray<TWeakObjectPtr<AActor>> Actors;
	
	for (auto CurrentActor : InActors)
	{
		if (!IsValid(CurrentActor))
			continue;

		Actors.Add(CurrentActor);
	}
	
	if (Actors.Num() > 0) // Only edit the context menu if any actors are selected.
	{
		// Add some actor menu extensions
		FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
		TSharedRef<FUICommandList> LevelEditorCommandBindings = LevelEditor.GetGlobalLevelEditorActions();
		Extender->AddMenuExtension(
			"ActorViewOptions",
			EExtensionHook::After,
			LevelEditorCommandBindings,
			FMenuExtensionDelegate::CreateLambda([this, Actors](FMenuBuilder& MenuBuilder)
		{
				MenuBuilder.AddMenuEntry(FULUCommands::Get()._SnapToActor);
				MenuBuilder.AddMenuEntry(FULUCommands::Get()._MatchActorSize);
		})
		);
	}
	return Extender;
}


void FUluToolsModule::BindMenuCommands()
{
	DefaultCommandList = MakeShareable(new FUICommandList);

	FULUCommands::Register();
	const FULUCommands& Commands = FULUCommands::Get();
	
	// Session 
	DefaultCommandList->MapAction(
		Commands._SnapToActor,
		FExecuteAction::CreateLambda([]() { return FULUCommands::SnapToActor(); }),
		FCanExecuteAction::CreateLambda([]() { return GEditor->GetSelectedActorCount()>1; }));

	DefaultCommandList->MapAction(
		Commands._MatchActorSize,
		FExecuteAction::CreateLambda([]() { return FULUCommands::MatchActorSize(); }),
		FCanExecuteAction::CreateLambda([]() { return GEditor->GetSelectedActorCount()>1; })); // Will grey out the menu entry if we don't have enough actors to snap.

	

	// Append the command to the editor module
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked< FLevelEditorModule >("LevelEditor");
	LevelEditorModule.GetGlobalLevelEditorActions()->Append(DefaultCommandList.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUluToolsModule, UluTools)

//@ToDo: Expose power saving button
