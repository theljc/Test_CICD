// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorUtilityTextRefreshHelper.h"

void UEditorUtilityTextRefreshHelper::TestNode_Internal()
{
	if (GEngine) {
		const int32 AlwaysAddKey = -1;

		GEngine->AddOnScreenDebugMessage(AlwaysAddKey,
			5.0f,
			FColor::Purple,
			TEXT("Hello World!")
		);
	}
}
