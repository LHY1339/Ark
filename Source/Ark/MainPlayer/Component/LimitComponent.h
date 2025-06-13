// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ark/Object/MainPlayerObject.h"
#include "Components/ActorComponent.h"
#include "LimitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARK_API ULimitComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void AddLimit(float NewValue, FString NewName);
	void RemoveLimit(FString NewName);
	bool IsLimitValid(FString NewName);
	float GetLimit(FString NewName);
	float GetLimit();

public:
	TArray<FFloatLimit> LimitList;
};
