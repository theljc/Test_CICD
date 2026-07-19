// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "BPNode_TestNode.generated.h"

/**
 * 
 */
UCLASS()
class MYBLUEPRINTNODEEDITOR_API UBPNode_TestNode : public UK2Node
{
	GENERATED_BODY()
public:
	// UEdGraphNode interface
	virtual void AllocateDefaultPins() override;

	virtual FText GetTooltipText() const override { return FText::FromString(TEXT("a hello world node")); }
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString(TEXT("Say Hello World")); }
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual FText GetMenuCategory() const override { return FText::FromString(TEXT("MyBlueprintNodes")); }
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// End of UK2Node interface
	
};
