#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Interact.generated.h"


class UButton;

UCLASS()
class ARK_API UUW_Interact : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UButton* Button_Base;

	UPROPERTY()
	AActor* InteractActor;
};
