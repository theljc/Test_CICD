// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateDescribion/StateTransitionTable.h"
#include "UObject/Object.h"
#include "VFStateMachineBase.generated.h"

struct FGameplayTag;
class UVFStateBase;
/**
 * 
 */
UCLASS()
class UNREALPCGEXAMPLES_API UVFStateMachineBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
private:
	TMap<UClass*, TArray<FVFStateTransition>> TransitionLookup;
	
	// Tick control
	bool bIsTickEnabled;
	TWeakObjectPtr<UWorld> CachedWorld;
    
public:
	// UVFStateMachineBase();
	
	// FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	
	// // State machine interface
	// void Initialize(const FVFStateMachineDefinition& Definition);
	// void Update(float DeltaTime);
	bool TryForceSetState(const TSubclassOf<UVFStateBase>& TargetStateClass, TArray<FGameplayTag>& OutFailReasons);
	void TransitionToState(TSubclassOf<UVFStateBase> StateClass);
	// void Shutdown();
	// void SetTickEnabled(bool bEnabled);
	// virtual void RegisterReplicatedSubObjects(AActor* Owner) { };
	// virtual void UnregisterReplicatedSubObjects(AActor* Owner) { };

	UFUNCTION(BlueprintPure, Category = "State Machine")
	const UVFStateBase* GetCurrentState() const { return CurrentState; }
	UVFStateBase* GetMutableCurrentState() { return CurrentState; }
	
private:
	// void BuildTransitionLookup();
	bool TryAutoTransition();

public:
	// Network Support, by default all FSM support replication automatically, but can of course remove it if your game doesn't need it
	// virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; };

private:
	UPROPERTY()
	TObjectPtr<UVFStateBase> CurrentState;
	
	FVFStateMachineDefinition StateMachineDefinition;

	TMap<TSubclassOf<UVFStateBase>, TArray<FVFStateTransition>> TransitionMap;

};
