#pragma once

#define DECLARE_STATE_MACHINE(MachineName) \
private: \
	static FVFStateMachineDefinition Create##MachineName##FSM(); \
	mutable TOptional<FVFStateMachineDefinition> Cached##MachineName##Definition; \
	\
public: \
	const FVFStateMachineDefinition& Get##MachineName##Definition() const \
	{ \
		if (!Cached##MachineName##Definition.IsSet()) \
		{ \
			Cached##MachineName##Definition = Create##MachineName##FSM(); \
		} \
		return Cached##MachineName##Definition.GetValue(); \
	} \
	\
	const UVF##MachineName##StateMachine* Get##MachineName##StateMachine() const \
	{ \
		return MachineName##StateMachine; \
	} \
	UVF##MachineName##StateMachine* GetMutable##MachineName##StateMachine() \
	{ \
		return MachineName##StateMachine; \
	}

#define IMPLEMENT_STATE_MACHINE(ClassName, MachineName) \
FVFStateMachineDefinition ClassName::Create##MachineName##FSM()

#define INITIALIZE_STATE_MACHINE(MachineName) \
	MachineName##StateMachine = NewObject<UVF##MachineName##StateMachine>(this, NAME_None, RF_Public | RF_Standalone); \
	MachineName##StateMachine->Initialize(Get##MachineName##Definition());

#define SHUTDOWN_STATE_MACHINE(MachineName) \
	if (IsValid(MachineName##StateMachine)) \
	{ \
		MachineName##StateMachine->Shutdown(); \
	}

#define STATE_TYPE(StateName) \
	UVF##StateName##State::StaticClass()

#define STATEMACHINE_TYPE(StateMachineName) \
	UVF##StateMachineName##StateMachine::StaticClass()
