// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "ULUStaticMeshAssetValidator.generated.h"

/**
 * 
 */
UCLASS()
class ULUTOOLS_API UULUStaticMeshAssetValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

public:
	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, UPARAM(ref) TArray<FText>& ValidationErrors) override;
};
