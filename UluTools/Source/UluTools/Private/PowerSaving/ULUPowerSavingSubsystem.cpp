// Copyright The First Ones, All Rights Reserved.


#include "PowerSaving/ULUPowerSavingSubsystem.h"
#include "Windows.h"
#include "Engine/EngineTypes.h"
#include "PowerSaving/ULUPowerSavingSettings.h"


UULUPowerSavingSubsystem::UULUPowerSavingSubsystem()
{
}


ETickableTickType UULUPowerSavingSubsystem::GetTickableTickType() const
{
	return FTickableGameObject::GetTickableTickType(); 
}


bool UULUPowerSavingSubsystem::IsAllowedToTick() const
{
	return bInitialized;
}


void UULUPowerSavingSubsystem::Tick(float DeltaTime)
{
	checkf(IsInitialized(), TEXT("Ticking should have been disabled for an uninitialized subsystem : remember to call IsInitialized in the subsystem's IsTickable, IsTickableInEditor and/or IsTickableWhenPaused implementation"));

	const UULUPowerSavingSettings* Settings = GetDefault<UULUPowerSavingSettings>();

	if (Settings->PowerSavingMode)
	{
		if(GetAsyncKeyState(VK_LBUTTON) < 0 || GetAsyncKeyState(VK_RBUTTON) < 0) //restart the timer if pressing the key
		{
			GetWorldEditor()->GetTimerManager().ClearTimer(IdleTimer);
			GetWorldEditor()->GetTimerManager().SetTimer(IdleTimer, this, &UULUPowerSavingSubsystem::OnIdleTimer, Settings->TimeToWaitBeforePowerSaving,  true);
			
			if(bPowerSaving)
			{
				if (UEditorEngine* UnrealEditor = Cast<UEditorEngine>(GEngine))
				{
					bPowerSaving = false;
		
					FText DisplayName = FText::FromString(TEXT("Powersaving mode editor freezing"));
					UnrealEditor->RemoveViewportsRealtimeOverride(DisplayName);
				}
			}
		}
	}
}


TStatId UULUPowerSavingSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UULUPowerSavingSubsystem, STATGROUP_Tickables);
}


void UULUPowerSavingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;
}


void UULUPowerSavingSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}


void UULUPowerSavingSubsystem::OnIdleTimer()
{
	if (UEditorEngine* UnrealEditor = Cast<UEditorEngine>(GEngine))
	{
		bPowerSaving = true;
		
		FText DisplayName = FText::FromString(TEXT("Powersaving mode editor freezing"));
		UnrealEditor->RemoveViewportsRealtimeOverride(DisplayName);
		UnrealEditor->SetViewportsRealtimeOverride(false, DisplayName);
	}
}


UWorld* UULUPowerSavingSubsystem::GetWorldEditor()
{
	auto& Contexts = GEditor->GetWorldContexts();
	for (auto& Context : Contexts)
	{
		EWorldType::Type WT = Context.WorldType.GetValue();
		switch (WT)
		{
		case EWorldType::EditorPreview:
			return Context.World();
		case EWorldType::Game:
			return nullptr;
		case EWorldType::Editor:
			return Context.World();
		case EWorldType::PIE:
			return nullptr;
		case EWorldType::GamePreview:
			return nullptr;
		case EWorldType::GameRPC:
			return nullptr;
		case EWorldType::Inactive:
			return nullptr;
		case EWorldType::None:
			return nullptr;
		}
	}
	return nullptr;
}


void UULUPowerSavingSubsystem::StartPowerSaving()
{
	if (GEngine)
	{
		GetWorldEditor()->GetTimerManager().SetTimer(IdleTimer, this, &UULUPowerSavingSubsystem::OnIdleTimer, 5.f,  true);
	}
}

void UULUPowerSavingSubsystem::StopPowerSaving()
{
	if (GEngine)
	{
		GetWorldEditor()->GetTimerManager().ClearTimer(IdleTimer);
			
		if(bPowerSaving)
		{
			if (UEditorEngine* UnrealEditor = Cast<UEditorEngine>(GEngine))
			{
				bPowerSaving = false;
		
				FText DisplayName = FText::FromString(TEXT("Powersaving mode editor freezing"));
				UnrealEditor->RemoveViewportsRealtimeOverride(DisplayName);
			}
		}
	}
}


