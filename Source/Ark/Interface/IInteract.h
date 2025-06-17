#pragma once

#include "CoreMinimal.h"
#include "Ark/Object/MainPickUpObject.h"
#include "UObject/Interface.h"
#include "IInteract.generated.h"


class AMainCharacter;

UINTERFACE(MinimalAPI)
class UIInteract : public UInterface
{
	GENERATED_BODY()
};


class ARK_API IIInteract
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	bool GetCanInteract(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	void SetWidgetCharacter(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	FPickUpProperty GetPickUpProperty(AMainCharacter* Character);
};
