#pragma once
#include "StateMachine/VFStateBase.h"
#include "StateMachine/StateDescribion/StateTransitionTable.h"

class FStateMachineBuilder
{
public:
	FStateMachineBuilder(TSubclassOf<UVFStateMachineBase> StateMachineClass)
	{
		Definition.StateMachineClass = StateMachineClass;
	}

	FStateMachineBuilder& Initial(TSubclassOf<UVFStateBase> State)
	{
		Definition.InitialState = State;
		return *this;
	}
    
	FStateMachineBuilder& From(TSubclassOf<UVFStateBase> State)
	{
		CurrentFrom = State;
		return *this;
	}
    
	FStateMachineBuilder& To(TSubclassOf<UVFStateBase> State)
	{
		checkf(CurrentFrom, TEXT("Cannot add transition without a 'From' state defined"));
		Definition.Transitions.Add({CurrentFrom, State});
		return *this;
	}
    
	FStateMachineBuilder& When(const TFunction<bool(const UVFStateMachineBase*)>& Condition)
	{
		if (Definition.Transitions.Num() > 0)
		{
			Definition.Transitions.Last().Condition = Condition;
		}
		return *this;
	}
    
	FVFStateMachineDefinition Build() { return MoveTemp(Definition); }

private:
	FVFStateMachineDefinition Definition;
	TSubclassOf<UVFStateBase> CurrentFrom = nullptr;
	
};
