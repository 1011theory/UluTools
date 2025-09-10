// Copyright The First Ones, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "ULUPowerSavingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ULUTOOLS_API UULUPowerSavingSubsystem : public UEditorSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UULUPowerSavingSubsystem();

	// FTickableGameObject implementation Begin
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsAllowedToTick() const override final;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableInEditor() const override {return true;}
	// FTickableGameObject implementation End

	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	bool IsInitialized() const { return bInitialized; }

private:
	bool bInitialized = false;
	
	//we need to bind to key input, and create a timer
	FTimerHandle IdleTimer;

	void OnIdleTimer();

	bool bPowerSaving = false;

	UWorld* GetWorldEditor();

public:
	UFUNCTION(BlueprintCallable)
	void StartPowerSaving();

	UFUNCTION(BlueprintCallable)
	void StopPowerSaving();
};
