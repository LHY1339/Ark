#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"


class AMainGameModeBase;

UCLASS()
class ARK_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMainGameStateBase();
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void Init_Default();

	void Tick_Calculate(float DeltaSeconds);

public:
	UPROPERTY(Replicated)
	float ServerDeltaTime = 0.0f;

private:
	UPROPERTY()
	AMainGameModeBase* GameMode;
};
