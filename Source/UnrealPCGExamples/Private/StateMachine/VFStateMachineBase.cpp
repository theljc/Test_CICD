// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/VFStateMachineBase.h"

#include "GameplayTagContainer.h"
#include "StateMachine/VFStateBase.h"

void UVFStateMachineBase::Tick(float DeltaTime)
{
	
}

bool UVFStateMachineBase::IsTickable() const
{
	return true;
}

TStatId UVFStateMachineBase::GetStatId() const
{
	return TStatId();
}

UWorld* UVFStateMachineBase::GetTickableGameObjectWorld() const
{
	return FTickableGameObject::GetTickableGameObjectWorld();
}

bool UVFStateMachineBase::TryForceSetState(const TSubclassOf<UVFStateBase>& TargetStateClass,
                                           TArray<FGameplayTag>& OutFailReasons)
{
	OutFailReasons.Empty();
    
	if (!TargetStateClass)
	{
		OutFailReasons.Add(FGameplayTag());
		return false;
	}
    
	// 验证状态是否存在于定义中
	bool bStateExists = TransitionMap.Contains(TargetStateClass);
	if (!bStateExists)
	{
		// 检查它是否是有效的目标状态
		for (const auto& TransitionPair : TransitionMap)
		{
			for (const auto& Transition : TransitionPair.Value)
			{
				if (Transition.ToState == TargetStateClass)
				{
					bStateExists = true;
					break;
				}
			}
			if (bStateExists) break;
		}
	}
    
	if (!bStateExists)
	{
		OutFailReasons.Add(FGameplayTag());
		return false;
	}
    
	TransitionToState(TargetStateClass);
	return true;
}

void UVFStateMachineBase::TransitionToState(TSubclassOf<UVFStateBase> StateClass)
{
	
}

bool UVFStateMachineBase::TryAutoTransition()
{
	if (!CurrentState) return false;
    
	const TArray<FVFStateTransition>* Transitions = TransitionMap.Find(CurrentState->GetClass());
	if (!Transitions) return false;
    
	for (const FVFStateTransition& Transition : *Transitions)
	{
		if (!Transition.Condition || Transition.Condition(this))
		{
			TransitionToState(Transition.ToState);
			return true; // First valid transition wins
		}
	}
	return false;
}
