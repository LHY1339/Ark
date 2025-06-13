#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MainPlayerCameraManager.generated.h"


UCLASS()
class ARK_API AMainPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AMainPlayerCameraManager();
	virtual void Tick(float DeltaSeconds) override;

private:
	void Init_Value();
};
