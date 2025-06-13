#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "StepPhysicalMaterial.generated.h"


UCLASS()
class ARK_API UStepPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	void PlayStep(const UObject* WorldContextObject, const FVector Location, float VolumeMultiply = 1.0f);

public:
	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Step = nullptr;

	UPROPERTY(EditAnywhere)
	float Volume = 1.0f;

	UPROPERTY(EditAnywhere)
	float Pitch = 1.0f;
};
