// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ULUBPL_Helpers.generated.h"

class UEditorUtilityWidgetBlueprint;
/**
 * 
 */
UCLASS()
class ULUTOOLS_API UULUBPL_Helpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*Creates a tab and spawns the specified Editor Utility Widget.*/
	UFUNCTION(BlueprintCallable, Category = UluTools)
	static void RunEditorUtilityWidget(UEditorUtilityWidgetBlueprint* EditorUtilityWidget);

	/*Returns editor viewport size, without relying on in-game features.*/
	UFUNCTION(BlueprintCallable, Category = UluTools)
	static FVector2D GetViewportSizeInEditor();
	
	UFUNCTION(BlueprintCallable, Category = UluTools)
	static bool ProjectWorldToScreenInEditor(const FVector& WorldLocation, FVector2D& OutScreenPosition);

	/*Unlike the default 'GetNumTriangles' function, this function returns the real Nanite tricount instead of the fallback mesh tricount.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = UluTools)
	static int GetNaniteConsciousPolycount(UStaticMesh* InMesh);
};
