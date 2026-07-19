// Fill out your copyright notice in the Description page of Project Settings.


#include "BPNode_TestNode.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "UnrealPCGExamples/Public/EditorUtilityTextRefreshHelper.h"

void UBPNode_TestNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

void UBPNode_TestNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
	
}

void UBPNode_TestNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	UEdGraphPin* ExecPin = GetExecPin();
	UEdGraphPin* ThenPin = GetThenPin();
	if (ExecPin && ThenPin) {
	
		// create a CallFunction node
		FName MyFunctionName = GET_FUNCTION_NAME_CHECKED(UEditorUtilityTextRefreshHelper, TestNode_Internal);
	
		UK2Node_CallFunction* CallFuncNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		// CallFuncNode->FunctionReference.SetExternalMember(MyFunctionName, UEditorUtilityTextRefreshHelper::StaticClass());
		// CallFuncNode->AllocateDefaultPins();
	
		// move pins
		// CompilerContext.MovePinLinksToIntermediate(*ExecPin, *(CallFuncNode->GetExecPin()));
		// CompilerContext.MovePinLinksToIntermediate(*ThenPin, *(CallFuncNode->GetThenPin()));
	}
	
	// break any links to the expanded node
	BreakAllNodeLinks();
	
}
