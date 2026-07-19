// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VFStateBase.generated.h"

class UVFStateMachineBase;
/**
 * 状态机的状态父类
 */
UCLASS()
class UNREALPCGEXAMPLES_API UVFStateBase : public UObject
{
	GENERATED_BODY()

public:
	UVFStateBase() {};
    
	/** Called when entering this state */
	virtual void EnterState(UVFStateMachineBase* StateMachine) {}

	/** Called when exiting this state */
	virtual void ExitState(UVFStateMachineBase* StateMachine) {}
    
	/** Called every frame while this state is active */
	virtual void UpdateState(UVFStateMachineBase* StateMachine, const float DeltaTime) {}

	virtual bool IsSupportedForNetworking() const override { return true; }

#if !UE_BUILD_SHIPPING
	/** Return debug information for this state - available in all non-shipping builds for debugging */
	virtual FString GetDebugInfo(const UVFStateMachineBase* StateMachine) const { return FString(); }
#endif

protected:
	/** Helper to get the current game state */
	class AVFGameState* GetGameState(const UVFStateMachineBase* StateMachine) const;
	
};
