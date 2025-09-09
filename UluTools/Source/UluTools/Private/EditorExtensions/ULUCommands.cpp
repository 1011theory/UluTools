// Copyright The First Ones, All Rights Reserved.


#include "EditorExtensions/ULUCommands.h"

#include "Selection.h"

#include "ULUIcons.h"

#define LOCTEXT_NAMESPACE "FUluToolsModule"

FULUCommands::FULUCommands()
: TCommands<FULUCommands>	(TEXT("Ulu Tools"), NSLOCTEXT("Contexts", "Ulu Tools", "Ulu Tools Plugin"), NAME_None, FUluIconsStyle::GetStyleSetName())
{
}


void FULUCommands::RegisterCommands()
{
	UI_COMMAND(_SnapToActor, "Snap To First Actor Selected", "Snaps all selected actors to the first actor selected in the viewport.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(_MatchActorSize, "Match Size Of First Actor Selected", "Makes all selected actors have the same size as the first actor selected.", EUserInterfaceActionType::Button, FInputChord());
	
}


void FULUCommands::SnapToActor()
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "SnapObjectToObject", "Snap Object to Object"));
	
	FScopedLevelDirtied LevelDirtyCallback; // Fires ULevel::LevelDirtiedEvent when falling out of scope.
	
	int32 ActorIndex = 0;
	FTransform TargetTransform;
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It, ++ActorIndex /* To track the first actor */)
	{
		AActor* CurrentActor = Cast<AActor>(*It);
		
		if (ActorIndex == 0)
		{
			TargetTransform = CurrentActor->GetTransform();
			continue;
		}
		if (IsValid(CurrentActor))
		{
			CurrentActor->Modify();
			CurrentActor->SetActorTransform(TargetTransform);
			CurrentActor->PostEditMove(true);
		}
	}
	
	LevelDirtyCallback.Request();
}


void FULUCommands::MatchActorSize()
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "MatchActorSize", "Match Actor Size"));
	FScopedLevelDirtied LevelDirtyCallback; // Fires ULevel::LevelDirtiedEvent when falling out of scope.

	int32 ActorIndex = 0;
	FVector Origin; FVector Bounds;
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It, ++ActorIndex /* To track the first actor */)
	{
		AActor* CurrentActor = Cast<AActor>(*It);
		
		if (ActorIndex == 0)
		{
			CurrentActor->GetActorBounds(false, Origin, Bounds);
			continue;
		}
		
		CurrentActor->Modify();
		
		FVector CurrentOrigin;
		FVector CurrentBounds;
		CurrentActor->GetActorBounds(false, CurrentOrigin, CurrentBounds);
		float DeltaBounds = Bounds.Length()/CurrentBounds.Length();
		CurrentActor->SetActorScale3D(CurrentActor->GetActorScale3D()*DeltaBounds);
		
		CurrentActor->PostEditMove(true);
	}
	LevelDirtyCallback.Request();
}
