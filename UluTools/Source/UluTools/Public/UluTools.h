// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUluToolsModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<FExtender> GetLevelViewportContextMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> InActors);

	TSharedRef<FExtender> GetLevelToolbarExtender(const TSharedRef<FUICommandList> CommandList);

	FDelegateHandle LevelViewportExtenderHandle;
	FDelegateHandle LevelToolbarExtenderHandle;

	// List of UI commands used by the various menus
	TSharedPtr<FUICommandList> DefaultCommandList;

	void BindMenuCommands();
};
