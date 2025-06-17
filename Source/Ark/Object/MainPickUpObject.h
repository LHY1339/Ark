#pragma once

#include "CoreMinimal.h"
#include "MainPickUpObject.generated.h"


USTRUCT(BlueprintType)
struct FPickUpProperty
{
	GENERATED_BODY()

	UPROPERTY()
	UTexture2D* Texture = nullptr;

	UPROPERTY()
	FString Name = "PickUp";

	UPROPERTY()
	FString Description = "This Is A PickUp Actor";

	UPROPERTY()
	FLinearColor BackColor;

	UPROPERTY()
	FLinearColor TextColor;
};

