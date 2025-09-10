// Copyright The First Ones, All Rights Reserved.


#include "ULUIcons.h"

#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FUluIconsStyle::StyleInstance = nullptr;

void FUluIconsStyle::Initialize()
{
	if (StyleInstance.IsValid()) return;

	StyleInstance = MakeShareable(new FSlateStyleSet("UluToolsStyle"));
    
	FString ContentDir = IPluginManager::Get().FindPlugin("UluTools")->GetBaseDir() / TEXT("Resources");
	StyleInstance->SetContentRoot(ContentDir);

	// Register your image as a brush
	StyleInstance->Set("UluTools.Icon", new FSlateImageBrush(ContentDir / TEXT("UluTools_Icon.png"), FVector2D(40.f, 40.f)));
	StyleInstance->Set("UluToolsStyle._MatchActorSize", new FSlateImageBrush(ContentDir / TEXT("UluTools_Icon.png"), FVector2D(40.f, 40.f)));
	StyleInstance->Set("UluToolsStyle._SnapToActor", new FSlateImageBrush(ContentDir / TEXT("UluTools_Icon.png"), FVector2D(40.f, 40.f)));
	StyleInstance->Set("UluToolsStyle._BatterySaver", new FSlateImageBrush(ContentDir / TEXT("UluTools_Icon.png"), FVector2D(40.f, 40.f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FUluIconsStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}
}

TSharedPtr<ISlateStyle> FUluIconsStyle::Get()
{
	return StyleInstance;
}

FName FUluIconsStyle::GetStyleSetName()
{
	return "UluToolsStyle";
}
