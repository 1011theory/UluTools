// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "Misc/SlowTask.h"
#include "Delegates/IDelegateInstance.h"

struct FSlowTask;

/*static const FName NodeSyncTabName("HoudiniNodeSync");
static const FName HoudiniToolsTabName("HoudiniTools");
static const FName ExamplesTabName("Examples");*/

// Class containing commands for Ulu Tools actions
class FULUCommands : public TCommands<FULUCommands>
{
public:

	FULUCommands();

	// TCommand<> interface
	virtual void RegisterCommands() override;


	/*Snaps all selected actors to the first actor selected in the level viewport. Applies the first actor's full transform. */
	static void SnapToActor();

	static void MatchActorSize();

	static void ToggleBatterySaver();

	static bool IsBatterySaveModeOn();
	
	TSharedPtr<FUICommandInfo> _SnapToActor;

	TSharedPtr<FUICommandInfo> _MatchActorSize;

	TSharedPtr<FUICommandInfo> _BatterySave;

	
	/*// Is PDG/BGEO commandlet enabled
	TSharedPtr<FUICommandInfo> _IsPDGCommandletEnabled;*/

protected:
	
};