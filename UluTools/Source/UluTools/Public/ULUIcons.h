// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

/**
 * Plugin Icon used in menus.
 */

class FUluIconsStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static TSharedPtr<class ISlateStyle> Get();
	static FName GetStyleSetName();

private:
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
};
