#include "StepPhysicalMaterial.h"

#include "Kismet/GameplayStatics.h"

void UStepPhysicalMaterial::PlayStep(const UObject* WorldContextObject, const FVector Location, float VolumeMultiply)
{
	UGameplayStatics::PlaySoundAtLocation(
		WorldContextObject,
		Sound_Step,
		Location,
		FRotator::ZeroRotator,
		Volume * VolumeMultiply,
		Pitch
	);
}
