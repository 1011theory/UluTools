// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ULUPowerSavingSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Ulu Tools Power Saving Settings"), Blueprintable)
class ULUTOOLS_API UULUPowerSavingSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Config)
	bool PowerSavingMode = true;

	UPROPERTY(EditDefaultsOnly, Config) //make in seconds
	float TimeToWaitBeforePowerSaving = 60.f;
};
