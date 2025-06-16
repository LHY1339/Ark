#include "StepPhysicalMaterial.h"

#include "Kismet/GameplayStatics.h"

void UStepPhysicalMaterial::PlayStep(const UObject* WorldContextObject, const FVector Location, float VolumeMultiply)
{
	const float pitch = FMath::FRandRange(Pitch - 0.1, Pitch + 0.1);
	UGameplayStatics::PlaySoundAtLocation(
		WorldContextObject,
		Sound_Step,
		Location,
		FRotator::ZeroRotator,
		Volume * VolumeMultiply,
		pitch
	);
}
