#include "MainGameModeBase.h"

AMainGameModeBase::AMainGameModeBase()
{
	Init_Default();
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Tick_Calculate(DeltaSeconds);
}

void AMainGameModeBase::Init_Default()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseSeamlessTravel = true;
}

void AMainGameModeBase::Tick_Calculate(float DeltaSeconds)
{
	ServerDeltaTime = DeltaSeconds;
}
