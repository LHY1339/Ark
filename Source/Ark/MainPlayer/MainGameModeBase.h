#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"


UCLASS()
class ARK_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameModeBase();
	virtual void Tick(float DeltaSeconds) override;

private:
	void Init_Default();

	void Tick_Calculate(float DeltaSeconds);

public:
	float ServerDeltaTime = 0.0f;
};
