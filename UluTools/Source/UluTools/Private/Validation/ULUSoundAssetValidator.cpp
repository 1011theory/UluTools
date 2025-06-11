// Copyright The First Ones, All Rights Reserved.

#include "Validation/ULUSoundAssetValidator.h"
#include "Sound/SoundCue.h"


bool UULUSoundAssetValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return InAsset->GetClass()->IsChildOf(USoundBase::StaticClass());
}


EDataValidationResult UULUSoundAssetValidator::ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors)
{
	if (const auto Sound = Cast<USoundBase>(InAsset))
	{
		if (!Sound->AttenuationSettings)
		{
			AssetWarning(InAsset, INVTEXT("Missing Attenuation class for this sound"));
		}
		if (!Sound->SoundClassObject)
		{
			AssetFails(InAsset, INVTEXT("Missing Sound Class"), ValidationErrors);
			return EDataValidationResult::Invalid;
		}
	}
	AssetPasses(InAsset);
	return EDataValidationResult::Valid;
}

