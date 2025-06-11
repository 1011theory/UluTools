// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ULUTypes_MaterialInstanceMaker.h"
#include "Engine/DataAsset.h"
#include "ULUDA_MaterialInstanceMaker.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ULUTOOLS_API UULUDA_MaterialInstanceMaker : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialInstanceMaker)
	FString TexturePrefix = TEXT("T_");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialInstanceMaker)
	FString StaticMeshPrefix = TEXT("SM_");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialInstanceMaker)
	FString MaterialInstancePrefix = TEXT("MI_");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialInstanceMaker)
	TArray <FULUTypes_MaterialInstanceMaker> TexturesData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialInstanceMaker)
	TObjectPtr<UMaterialInstance> BaseMaterial;
};
