// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ULUDevSettings.generated.h"

class UULUDA_Rules;
class UULUDA_MaterialInstanceMaker;
struct FULUTypes_MaterialInstanceMaker;
/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Ulu Tools Developer Settings"), Blueprintable)
class ULUTOOLS_API UULUDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = UluTools)
	TSoftObjectPtr<UULUDA_MaterialInstanceMaker> MaterialInstanceMakerRules;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = UluTools)
	TSoftObjectPtr<UULUDA_Rules> UluToolsRules;
};
