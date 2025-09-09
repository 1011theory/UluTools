// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ULUBPL_PowerSaving.generated.h"

/**
 * 
 */
UCLASS(meta=(ScriptName="PowerSavingLibrary"))
class ULUTOOLS_API UULUBPL_PowerSaving : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = UluTools)
	static void FreezeEditorRendering(bool bFreeze);

	
	UFUNCTION(BlueprintCallable, Category = UluTools)
	static bool IsLeftMouseButtonDown();
};
