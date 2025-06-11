// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ULUDA_Rules.generated.h"

/**
 * Defines rules and references for Ulu Tools operations.
 */
UCLASS()
class ULUTOOLS_API UULUDA_Rules : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UluTools)
	TObjectPtr<URuntimeVirtualTexture> MeshInteractionRuntimeVirtualTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UluTools)
	TObjectPtr<USoundClass> SoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UluTools)
	TObjectPtr<USoundAttenuation> SoundAttenuationClass;

	
};
