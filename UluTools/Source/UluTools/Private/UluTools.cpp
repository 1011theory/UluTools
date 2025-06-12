// Copyright Epic Games, Inc. All Rights Reserved.

#include "UluTools.h"

#include "ULUIcons.h"

#define LOCTEXT_NAMESPACE "FUluToolsModule"

void FUluToolsModule::StartupModule()
{
	FUluIconsStyle::Initialize();
}

void FUluToolsModule::ShutdownModule()
{
	FUluIconsStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUluToolsModule, UluTools)