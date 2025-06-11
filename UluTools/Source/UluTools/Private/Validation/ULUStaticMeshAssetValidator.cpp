// Copyright The First Ones, All Rights Reserved.

#include "Validation/ULUStaticMeshAssetValidator.h"
#include "PhysicsEngine/BodySetup.h"


bool UULUStaticMeshAssetValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return InAsset->GetClass()->IsChildOf(UStaticMesh::StaticClass());
}


EDataValidationResult UULUStaticMeshAssetValidator::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
	const UStaticMesh* SM = Cast<UStaticMesh>(InAsset);

	if (!SM->NaniteSettings.bEnabled)
	{
		if (SM->GetNumTriangles(0) > 10000)
		{
			AssetWarning(InAsset, INVTEXT("Non-Nanite Static Mesh has more than 10k triangles. Consider converting the mesh to nanite"));
		}
		if (SM->GetNumLODs()<=1)
		{
			AssetWarning(InAsset, INVTEXT("Non-Nanite Static Mesh is missing LODs"));
		}
	}
	
	ECollisionTraceFlag TraceFlag = SM->GetBodySetup()->GetCollisionTraceFlag();
	if (TraceFlag == ECollisionTraceFlag::CTF_UseComplexAsSimple && (SM->GetNumTriangles(0)>50 || SM->GetNumNaniteTriangles()>50)) // complex collision only because a problem if the mesh has a high enough polycount, so we check this before warning.
	{
		AssetFails(InAsset, INVTEXT("Static Mesh is using complex collision as default collision. Replace with an optimized collision mesh to avoid performance hits"), ValidationErrors);
	}
	AssetPasses(InAsset);
	return EDataValidationResult::Valid;
}
