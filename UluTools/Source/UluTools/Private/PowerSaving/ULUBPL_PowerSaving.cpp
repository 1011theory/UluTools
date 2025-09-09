// Copyright The First Ones, All Rights Reserved.


#include "PowerSaving/ULUBPL_PowerSaving.h"
#include "Windows.h"

void UULUBPL_PowerSaving::FreezeEditorRendering(bool bFreeze)
{
#if WITH_EDITOR
	if (UEditorEngine* UnrealEditor = Cast<UEditorEngine>(GEngine))
	{
		FText DisplayName = FText::FromString(TEXT("Powersaving mode editor freezing"));
		if (bFreeze)
		{
			UnrealEditor->RemoveViewportsRealtimeOverride(DisplayName);
			UnrealEditor->SetViewportsRealtimeOverride(!bFreeze, DisplayName); //we actually dont want to set an override if we are not meaning to freeze it
		}
		else
		{
			UnrealEditor->RemoveViewportsRealtimeOverride(DisplayName); //to prevent it from stacking multiple overrides of this type.
		}
		
		
	}
#endif
}

bool UULUBPL_PowerSaving::IsLeftMouseButtonDown()
{
	if(GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		return true;
	}
	return false;
}

//next: we want to listen for any user input (mouse or keyboard). We want to set a timer for editor inactivity, and restart it whenever there is user INPUT
//we likely want to make a an editor subsystem that runs as long as the editor runs, and run the logic from there.