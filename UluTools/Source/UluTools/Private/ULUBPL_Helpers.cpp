// Copyright The First Ones, All Rights Reserved.

#include "ULUBPL_Helpers.h"
#include "Editor.h"
#include "EditorUtilitySubsystem.h"


#if WITH_EDITOR

void UULUBPL_Helpers::RunEditorUtilityWidget(UEditorUtilityWidgetBlueprint* EditorUtilityWidget)
{
	if (EditorUtilityWidget)
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		EditorUtilitySubsystem->SpawnAndRegisterTab(EditorUtilityWidget);
	}
}


FVector2D UULUBPL_Helpers::GetViewportSizeInEditor()
{
	if (FViewport* Viewport = GEditor->GetActiveViewport())
	{
		return Viewport->GetSizeXY();
	}
	return FVector2D::Zero();
}


bool UULUBPL_Helpers::ProjectWorldToScreenInEditor(const FVector& WorldLocation, FVector2D& OutScreenPosition)
{
	FViewport* Viewport = GEditor->GetActiveViewport();
	if (!Viewport) return false;

	FEditorViewportClient* ViewportClient = static_cast<FEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());
	if (!ViewportClient) return false;

	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		Viewport,
		ViewportClient->GetScene(),
		ViewportClient->EngineShowFlags));

	FSceneView* SceneView = ViewportClient->CalcSceneView(&ViewFamily);

	if (!SceneView) return false;

	const FMatrix& ViewProjectionMatrix = SceneView->ViewMatrices.GetViewProjectionMatrix();
	const FIntRect ViewRect = SceneView->UnscaledViewRect;

	FVector4 Projected = ViewProjectionMatrix.TransformFVector4(FVector4(WorldLocation, 1.f));
	if (Projected.W == 0.0f) return false;

	// Normalize and convert to screen coordinates
	const float InvW = 1.0f / Projected.W;
	const float X = (Projected.X * InvW * 0.5f + 0.5f) * ViewRect.Width() + ViewRect.Min.X;
	const float Y = (1.0f - (Projected.Y * InvW * 0.5f + 0.5f)) * ViewRect.Height() + ViewRect.Min.Y;

	OutScreenPosition = FVector2D(X, Y);
	return true;
}


int UULUBPL_Helpers::GetNaniteConsciousPolycount(UStaticMesh* InMesh)
{
	if(!InMesh){return 0;}

	if(InMesh->NaniteSettings.bEnabled)
	{
		return InMesh->GetNumNaniteTriangles();
	}
	return InMesh->GetNumTriangles(0);
}

#endif
