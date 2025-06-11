#include "MainGameStateBase.h"

#include "MainGameModeBase.h"
#include "Net/UnrealNetwork.h"

AMainGameStateBase::AMainGameStateBase()
{
	Init_Default();
}

void AMainGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Tick_Calculate(DeltaSeconds);
}

void AMainGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameStateBase, ServerDeltaTime)
}

void AMainGameStateBase::Init_Default()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainGameStateBase::Tick_Calculate(float DeltaSeconds)
{
	if (!HasAuthority())
	{
		return;
	}
	if (!GameMode)
	{
		GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
		return;
	}
	ServerDeltaTime = GameMode->ServerDeltaTime;
}
