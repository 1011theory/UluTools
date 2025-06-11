// Copyright The First Ones, All Rights Reserved.

#include "Validation/ULUSkeletalAssetValidator.h"


bool UULUSkeletalAssetValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	const UClass* AssetClass = InAsset->GetClass();

	return AssetClass->IsChildOf(USkeletalMesh::StaticClass());
}


EDataValidationResult UULUSkeletalAssetValidator::ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors)
{
	if (auto SKM = Cast<USkeletalMesh>(InAsset))
	{
		if (SKM->GetLODNum()<=1)
		{
			AssetWarning(InAsset, INVTEXT("This skeletal mesh needs LODs"));
		}
	}
	AssetPasses(InAsset);
	return EDataValidationResult::Valid;
}
