#pragma once

#include "CoreMinimal.h"
#include "MainPlayerObject.generated.h"


USTRUCT()
struct FUpdateVariable
{
	GENERATED_BODY()

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float AirSpeed;

	UPROPERTY()
	float Direction;

	UPROPERTY()
	float Pitch;

	UPROPERTY()
	bool Crouch;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;
};

USTRUCT()
struct FAnimVariable
{
	GENERATED_BODY()

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float AirSpeed;

	UPROPERTY()
	float Direction;

	UPROPERTY()
	float Pitch;

	UPROPERTY()
	bool Crouch;
};

USTRUCT()
struct FFloatLimit
{
	GENERATED_BODY()

	UPROPERTY()
	float Value;

	UPROPERTY()
	FString Name;
};