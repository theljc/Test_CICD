#pragma once

class UVFStateBase;
class UVFStateMachineBase;

struct FVFStateTransition
{
	TSubclassOf<UVFStateBase> FromState;
	TSubclassOf<UVFStateBase> ToState;
	TFunction<bool(const UVFStateMachineBase*)> Condition = nullptr;
};

struct FVFStateMachineDefinition
{
	TSubclassOf<UVFStateMachineBase> StateMachineClass;
	TSubclassOf<UVFStateBase> InitialState;
	TArray<FVFStateTransition> Transitions;
};
