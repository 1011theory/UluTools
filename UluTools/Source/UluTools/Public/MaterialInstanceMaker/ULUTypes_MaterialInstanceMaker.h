// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ULUTypes_MaterialInstanceMaker.generated.h"

/**
 * Struct that holds data for mapping texture types to material parameters.
 */
USTRUCT(BlueprintType)
struct FULUTypes_MaterialInstanceMaker
{
	GENERATED_BODY()

public:
	// Suffix used to identify the texture (e.g., "_ORM", "_N", "_C")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialInstanceMaker")
	FString TextureSuffix;

	// Expected compression setting for the texture
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialInstanceMaker")
	TEnumAsByte<TextureCompressionSettings> TextureCompSettings = TC_Default;

	// Name of the texture parameter in the material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialInstanceMaker")
	FString TextureParameterName;
};
