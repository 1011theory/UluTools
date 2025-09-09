// Copyright The First Ones, All Rights Reserved.


#include "Validation/ULUAnimationAssetValidator.h"


bool UULUAnimationAssetValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return InAsset && InAsset->GetClass() == UAnimSequence::StaticClass();
}


EDataValidationResult UULUAnimationAssetValidator::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
	if (const auto Animation = Cast<UAnimSequence>(InAsset))
	{
		FFrameRate FR = Animation->GetSamplingFrameRate();
		int32 FPS = FR.Numerator;
		
		if (FPS > 120) //#ToDo: Allow users to customize max allowed frame rate from Dev Settings.
		{
			AssetWarning(InAsset, FText::Format(INVTEXT("This animation has a frame rate of {0}. This will unnecessarily bloat up disk size. Consider reducing the animation frame rate to 120fps or less"), FPS));
		}
	}
	AssetPasses(InAsset);
	return EDataValidationResult::Valid;
}
