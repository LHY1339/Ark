#include "MainPlayerCameraManager.h"

AMainPlayerCameraManager::AMainPlayerCameraManager()
{
	Init_Value();
}

void AMainPlayerCameraManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainPlayerCameraManager::Init_Value()
{
	PrimaryActorTick.bCanEverTick = true;

	ViewPitchMax = 80.0f;
	ViewPitchMin = -80.0f;
}
