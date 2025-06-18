#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class ARK_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PawnLeavingGame() override;
};
