// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorUtilityTextRefreshHelper.generated.h"

/**
 * Helper library for refreshing localized text in Editor Utility Widgets
 */
UCLASS()
class UNREALPCGEXAMPLES_API UEditorUtilityTextRefreshHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void TestNode_Internal();
	
};
