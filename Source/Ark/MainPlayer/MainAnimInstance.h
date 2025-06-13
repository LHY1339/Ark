#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"


class AMainCharacter;

UCLASS()
class ARK_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//override
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//NativeUpdate
	void Update_GetVariable(float DeltaSeconds);

	//Reflection
	UFUNCTION()
	void AnimNotify_StepLeft();

	UFUNCTION()
	void AnimNotify_StepRight();

private:
	void Step(FName SocketName);

public:
	//Blueprint
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	float AirSpeed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;

	UPROPERTY(BlueprintReadOnly)
	float Pitch;

	UPROPERTY(BlueprintReadOnly)
	FVector CameraOffset;

	UPROPERTY(BlueprintReadOnly)
	float AnimSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool Crouch;

private:
	UPROPERTY()
	AMainCharacter* Character;
};
