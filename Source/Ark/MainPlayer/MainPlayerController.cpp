#include "MainPlayerController.h"

#include "MainCharacter.h"

void AMainPlayerController::PawnLeavingGame()
{
	Super::PawnLeavingGame();
	AMainCharacter* character = Cast<AMainCharacter>(GetPawn());
	if (character)
	{
		character->OnPawnLeavingGame(this);
	}
}
